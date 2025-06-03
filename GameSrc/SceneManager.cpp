#include "SceneManager.h"

SceneManager::SceneManager(sf::RenderWindow* window, unsigned int windowWidth, unsigned int windowHeight, bool editMode)
{
	srand(time(0));  
	// mutex that controls when the menus will begin loading 
	m_menuCanLoad.lock();
	m_window = window; 
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
	std::cout << "initialising scene manager:" << std::endl;
	m_editMode = editMode;
	// allocate memory that will be tracked via unique ptrs for each object that will only have a single instance within the game 
	m_textureManager = std::make_unique<TextureManager>(TextureManager()); 
	m_textureManager.get()->loadTextures(m_pathToTextures);
	m_textureManager.get()->loadAnims(m_pathToAnims);
	m_spriteGenerator = std::make_unique<SpriteGenerator>(SpriteGenerator(m_textureManager.get()));
	m_inputManager = std::make_unique<InputManager>(InputManager(m_window)); 
	m_camera = std::make_unique<Camera>(Camera(window, sf::FloatRect(0, 0, window->getSize().x, window->getSize().y)));
	m_player = std::make_unique<Player>(Player( sf::Vector2f(window->getSize()) / 2.0f, m_spriteGenerator.get(), m_inputManager.get(),m_camera.get())); 
	// as level generator has its own resoruces within the class allocated on the heap but it is a single object that is easy to track(as it exists for the life time of the prorgam) 
	// here we use a raw pointer that is simply deleted at the end of the program
	m_levelGenerator = new LevelGenerator(m_spriteGenerator.get(), sf::Vector2f(window->getSize()) / 2.0f,m_player.get(), sf::Vector2i(64, 64), sf::Vector2f(512.0f, 512.0f), sf::Vector2i(2, 2));
	m_menuCanLoad.unlock();
	// initialise a thread to load the main splash screen for the game 
	m_loadingMenuSplashScreen = std::thread(&SceneManager::loadMenuSplashScreen,this,window);
	// initilaise a thread to load the user details file 
	m_loadUserFileData = std::thread(&SceneManager::readUserDataFile, this);


}

SceneManager::~SceneManager()
{ 
	delete m_levelGenerator;
	// join the threads to the main thread in the destructor of the scene manager meaning that the game has been closed 
	// ensuring that there are no hanging threads left behind
    m_loadUserFileData.join();
	m_loadingMenuSplashScreen.join();
	
	
}

void SceneManager::draw()
{
	
	if (m_menuLoadingComplete) {
		if (m_menuManager->isDrawingOutOfGameMenus()) {
			m_menuManager->draw(m_window);
		}
		else {

			m_levelGenerator->drawObjects(m_window);
			m_player.get()->draw(m_window);
		}
	}
	
}

void SceneManager::update(float dt,sf::Event & event)
{
	
		m_inputManager->pollEvents(event);
		if (m_menuLoadingComplete) {
		  if (m_menuManager->isDrawingOutOfGameMenus()) {

			m_menuManager->update(dt);

		  }
		  else {
				m_levelGenerator->setPlayerIsInLevel(true);
				m_levelGenerator->update(dt);
		  }
		}
		m_inputManager->endFrame();

  

}

void SceneManager::loadMenuSplashScreen(sf::RenderWindow * window)
{
	std::cout << "thread to load menu splashScreen launched" << std::endl;
	// lock the mutex that manages the loading of the menu indicating to all threads that should wait  
	// until the menu is loaded to block until this mutex is unlocked 
	m_loadingMenuMutex.lock(); 
	// this mutex manages when the menu can actauly begin loading meaning the thread using this method will
	// block until this particualr mutex becomes unlocked 
	m_menuCanLoad.lock();
	std::cout << "menu can now load" << std::endl;
	std::cout << "loading splash screen menu on seperate Thread" << std::endl;
	m_menusPresentInScene = { std::make_shared<MainMenu>(window,m_inputManager.get(),m_spriteGenerator.get()) };
	m_menuManager = std::make_unique<MenuManager>(MenuManager(m_menusPresentInScene, 0, m_editMode));
	std::cout <<  "loading finished for splash screen on seperate thread momentarily sleeping" << std::endl;
	
	// as some other threads may be using unique guard for deffered locking it is 
	// important to unlock the mutex that causes those threads to wait until the 
	// menu loading is complete before notifying them via the contional variable that the unquie guard uses 
	// to start their execution 
	m_loadingMenuMutex.unlock();
	// set the boolean being used to manage when other threads can executed if the menu has loaded or not to true 
	// which means the .wait() method used by the contional vairable will stop blocking 
	m_menuLoadingComplete = true;  
	std::cout << "notifying file loading process to begin loading" << std::endl;
	// notify the thread used to load the csv into txt that it can now check its contional variable 
	// to see if the thread can begin execution, as we have finished loading the menu's and can now begin 
	//processing the csv file in the background 
	m_menuLoadingCompleteCvar.notify_one();
	// ensure to unlock all mutexes that were locked by this thread to avoid hangging threads that may constinously block 
	// mutexes are not properly unlcoked after use by a thread 
	m_menuCanLoad.unlock();

}

void SceneManager::readUserDataFile() 
{
	std::cout << "thread to read user data launched " << std::endl;
	// reads the provided csv file into a text file  
	// usuing a unquie lock for deffered blocking which will force the thread running this method to load 
	// the csv inot a txt file to wait until the menu loading is finished and then begin loading the csv 
	// file into the txt while the menu is running(not loading)
	std::unique_lock<std::mutex> waitForMenuToLoad(m_loadingMenuMutex);
	m_menuLoadingCompleteCvar.wait(waitForMenuToLoad, [this] {return m_menuLoadingComplete; });

	std::cout << "unblocking menu splash screen loaded proceeding to load user data from file " << std::endl;
	std::cout << "sleeping before loading file" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2)); // sleep the thread for two seconds then load the file 
	
	std::cout << "csv to txt read start " << std::endl;
	std::ifstream fileData;
	fileData.open(m_userDetails);

	if (!fileData.is_open()) {

		std::cout << "could not get user details from path " << m_userDetails << std::endl;
		return;
	}

	std::string line;
	std::ofstream fileDataOutput("../Assets/UserDetails/userDetails.txt");
	std::string lineDescriptor = "";
	int lineNum = 0;
	while (std::getline(fileData, line))
	{
		// ignore the line descriptor 
		if (lineDescriptor == "") {

			lineDescriptor = line;
			std::cout << "line descriptor " << line << std::endl;
			continue;
		}
		std::cout << "line in csv data: " << line << std::endl;
		fileDataOutput << lineNum << line + "\n"; 
		// push  the parsed user details into a vector 
		m_userData.push_back(line);
		std::cout << "sleeping momentarily after writing to file " << std::endl; 
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		lineNum++;
		
		
	}
	fileData.close();
	fileDataOutput.close();
	std::cout << "FINISHED READING CSV INTO TXT" << std::endl;
	std::cout << "reading csv into txt FINISHED thread for this process momentarily sleeping" << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(5));
}



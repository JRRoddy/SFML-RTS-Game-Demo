#include "Menu.h"


Menu::Menu(sf::RenderWindow* window, InputManager* inputManager)
{
	m_window = window;
	m_inputManager = inputManager;
	m_draggingElementSelected = false;
}


Menu* Menu::getActiveMenu()
{
	// if we have an active sub menu return the refernce to it
	if (m_hasActiveSubMenu) {
		return m_activeSubmenu;
	}
	// other wise return the current menu we are on
	return this;
}
// used to read particular ui data from a file 
void Menu::parseUIdata()
{
	std::ifstream file;

	file.open(m_menuUiDataPath);
	// if the input stream object opened the ui file data 
	if (file.is_open()) {
		std::string line;

		std::map<std::string, Button>::iterator button = m_buttons.begin();
		std::istringstream input;
		std::cout << "found ui data path: " << m_menuUiDataPath << std::endl;
		// go through all the lines in the file and read the ui data 
		while (std::getline(file, line)) {
		    // if we encounter a atext object position
			if (line.find("TPos:")) {
				// erase the line identifier leaving just the data 
				line.erase(0, line.find(":") + 1);
				// set the input stream object current string buffer to contain the line
				input.str(line); 
				std::cout << "parsing ui data " << line << std::endl;
				// read in the text object positions 
				float x, y;
				input >> x;
				input >> y;
				std::cout << "x:" << x << " y:" << y << std::endl;
				// if we havent reached the end of the map 
				// via the defined itterator above 
				if (button != m_buttons.end()); {
					// set the text object position of the current button we are targetting 
					button->second.setTextPos(sf::Vector2f(x, y));
					// increment the itterator to the next button object contained in the map
					button++; 
					// clear the input sstream for the next piece of ui data to be parsed 
					input.clear();
					input.str("");
					continue;
				}
				std::cout << "line amout greater than number of buttons check file " << m_menuUiDataPath << std::endl;




			}



		}
	}
	else {
		std::cout << "could not get ui data at path " << m_menuUiDataPath << std::endl;
	}
	file.close();
}

// update function for when te menu is in edit mode 
void Menu::editModeUpdate(float dt)
{
	// if we dont have an active sub menu update this menu 
	// using its edit mode methods 
	if (!m_hasActiveSubMenu) {
		editButtons();
		saveUiData();
		return;
	}
	// other wise if we have an active sub menu that should not draw
	// reset the values assostiated with the active sub menu and move back up one 
	// level to this menu 
	if (m_hasActiveSubMenu && !m_activeSubmenu->shouldDraw()) {
		m_hasActiveSubMenu = false;
		m_activeSubmenu = nullptr;
	}
	else {
		// other wise we have an active sub menu we need to edit
		m_activeSubmenu->editModeUpdate(dt);
	}



}
// used to save any ui data such as the positions of text 
// when the UI of a particualr menu has been edited in edit mode 
void Menu::saveUiData() {
	if (m_inputManager->keyReleased(sf::Keyboard::S)) {
		saveTextPositions();
		std::cout << "saving ui data" << std::endl;
	}

}

void Menu::initSubMenus()
{
	
}


//  method that is used to edit properties of 
// buttons within a particualr menu when the scene is in edit mode 
void Menu::editButtons() {

	// currrent selected text 
	sf::Text* selected = nullptr;
	//track mouse pos to ensure that elements can be moved and dragged by mouse 
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*m_window));
	// current clicked element 
	m_clickedElementId = "";
	// using an itterator to go through all the buttons in a map 
	for (std::map<std::string, Button>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++) {

		// if the text associated with a particualr button object contains the mouse positions
		if (it->second.getTextRef()->getGlobalBounds().contains(mousePos))
		{
			// if the mouse is held down i.e user is trying to drag the text
			if (m_inputManager->isMouseDown(sf::Mouse::Left)) {
				// set the current text ref to the text object 
				// assocatied with the current button being itterated through 
				selected = it->second.getTextRef();
				// centre the text on the mouse and allow it to be dragged around 
				selected->setPosition(mousePos);
				break;
			}
			// if enter is pressed and we are hovering a button 
			if (m_inputManager->keyReleased(sf::Keyboard::Enter)) {
				// element is considered to be clicked when in edit mode
				m_clickedElementId = it->second.getButtonId();
				// update any ui bindings and call any methods bound to the 
				// button id via method ptrs 
				updateUiBindings();
				try {
					// attempt to access a sub menu assosiated with the button
					std::cout << "clicked element id set to " << m_clickedElementId << std::endl;
					m_activeSubmenu = m_subMenus.at(it->second.getLinkedMenuId()).get();
					std::cout << "set sub menu to " << it->first << std::endl;
					m_activeSubmenu->setShouldDraw(true);
					m_hasActiveSubMenu = true;
				}
				catch (...) {
					std::cout << "button sub menu not found button id:" << it->first << " not found " << std::endl;
				}


				break;
			}



		}

	}



}


void Menu::draw(sf::RenderWindow* window)
{
	// if we have an active sub menu move down one level and draw it 
	if (m_hasActiveSubMenu) {
		m_activeSubmenu->draw(window);
		return;
	}
	// other wise we draw this menu 
	drawButtons(window);
	drawTextObjects(window);
	drawSliders(window);
	window->draw(m_menuHeaderText);
}


void Menu::update()
{

	// if we dont have a active sub menu we update this menu 
	if (!m_hasActiveSubMenu) {
		updateUI();
		updateUiBindings();
		return;
	}
	// if we do have an active sub menu and we shouldnt draw it 
	// we move back up to this menu reseting the values for the active sub menu 
	if (m_hasActiveSubMenu && !m_activeSubmenu->shouldDraw()) {
		m_hasActiveSubMenu = false;
		m_activeSubmenu = nullptr;
	}
	else {
		// otherwise we have an active sub menu we need to update 
		m_activeSubmenu->update();
	}


}

void Menu::resetSelectedElementIds() {
	// if mouse released any selected ui element that required drag is no longer selected
	if (m_inputManager->mouseReleased(sf::Mouse::Left) && m_draggingElementSelected) {
		m_draggingElementId = "";
		m_draggingElementSelected = false;
	}
	// each time we update we set the clicked element id to "" ready to detect any other 
	// ui elements being clicked next frame 
	m_clickedElementId = "";
}
// calls all methods to update particualr ui elements such as the updateButtons method 
void Menu::updateUI() {
		
	resetSelectedElementIds();
	updateButtons();
	updateSliders();


}


void Menu::drawTextObjects(sf::RenderWindow* window) {

	for (std::vector<sf::Text>::iterator it = m_textObjects.begin(); it != m_textObjects.end(); it++) {
		window->draw(*it);

	}
}

void Menu::drawButtons(sf::RenderWindow* window)
{
	for (std::map<std::string, Button>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++) {

		it->second.draw(window);
	}
}

void Menu::drawSliders(sf::RenderWindow* window)
{
	for (std::map<std::string,UiSlider>::iterator it = m_sliders.begin(); it != m_sliders.end(); it++) {

		it->second.draw(window);
	}


}

void Menu::updateButtons()
{

	// itterate through the std::map that contains all the buttons mapped to a particualr string id
	for (std::map<std::string, Button>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++) {
		// if the mouse is contained within the button bounds and is clicked 
		if (it->second.getShape().getGlobalBounds().contains(sf::Vector2f(m_inputManager->getMousePos())) &&
			m_inputManager->mouseReleased(sf::Mouse::Left))
		{
			try {
				// set the current clicked element id to the button string id 
				// which is used to access a particualr method pointer that 
				// is bound to that button id 
				m_clickedElementId = it->second.getButtonId();
				std::cout << "clicked element id set to " << m_clickedElementId << std::endl;
				// if the button leads to a particualr sub menu this line will not 
				// throw an expection and will set the current active sub menu to 
				// the sub menu object that is mapped to a particualr sub menu string id 
				// that the button object stores 
				m_activeSubmenu = m_subMenus.at(it->second.getLinkedMenuId()).get();
				std::cout << "set sub menu to " << it->first << std::endl;
				// set up flags for the sub menu to become active 
				m_activeSubmenu->setShouldDraw(true);
				m_hasActiveSubMenu = true;
			}
			catch (...) {
			}

		}

	}
}
void Menu::updateSliders()
{
	for (std::map<std::string, UiSlider>::iterator it = m_sliders.begin(); it != m_sliders.end(); it++){
		if (it->second.getIndicatorContainerBounds().contains(m_inputManager->getMousePos()) && 
			m_inputManager->isMouseDown(sf::Mouse::Left) && !m_draggingElementSelected) {
			std::cout << "setting id " << std::endl;
			m_draggingElementId = it->second.getElementId();
			m_draggingElementSelected = true;


		}




	}
	updateSelectedSlider();
}

void Menu::updateSelectedSlider()
{
	if (m_draggingElementId != "") {
		try {
			UiSlider& selectedSlider = m_sliders.at(m_draggingElementId);
			sf::Vector2f mouseToGlobal = m_window->mapPixelToCoords(m_inputManager->getMousPosPixel());
			selectedSlider.interpolateIndicatorPosX(m_inputManager->getMousePos());
		}
		catch (...) {
			std::cout << "dragging element " << m_draggingElementId << "not found " << std::endl;
		
		}
	}
}



bool Menu::shouldDraw() const
{
	return m_shouldDraw;
}
void Menu::setShouldDraw(bool shouldDraw)
{
	m_shouldDraw = shouldDraw;
}

//  used to save the positions of text objects associated with buttons 
// for the menu writing to a file to then be loaded by the parseUi data 
// method of the menu class allowing for easy positioning of text that needs to
// be placed on buttons 
void Menu::saveTextPositions()
{
	// if we have an active sub menu we go down one level 
	// and call that sub menu's save text object positions of that particualr sub menu
	if (m_hasActiveSubMenu) {

		m_activeSubmenu->saveTextPositions();
		return;
	}
	// use an output stream object to write to a file and open it(will also create it if neccessary)
	std::ofstream file(m_menuUiDataPath);
	std::cout << "saving data for ui path is:" << m_menuUiDataPath << std::endl;
	if (!file.is_open()) {
		std::cout << "could not find path to ui data " << m_menuUiDataPath << std::endl;
	}
	std::string textData = "";
	// itterate through the the buttons that have text and get their text object 
	// positions and save them to a file using the output stream object above 
	for (std::map<std::string, Button>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++) {
		textData = std::to_string(it->second.getTextPosition().x) + " " + std::to_string(it->second.getTextPosition().y);
		std::cout << "saving text data " << textData << std::endl;
		std::string fullText = "Tpos:" + textData + "\n";
		std::cout << "full text data " << fullText << std::endl;
		file << fullText;
	}
	// ensure to close the file after use 
	file.close();


}
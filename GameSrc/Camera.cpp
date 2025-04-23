#include "Camera.h"
// camera class that manipluates a view object 
// assigned to particualr window
Camera::Camera(sf::RenderWindow* window, sf::FloatRect& initialArea):m_cameraView(initialArea)
{
	m_window = window;
	m_window->setView(m_cameraView);


}

void Camera::setPosition(sf::Vector2f& centrePos)
{
   
	m_cameraView = m_window->getView(); // get current view

	m_cameraView.setCenter(centrePos); //set new center 

	m_window->setView(m_cameraView); /// reset view 

}

 sf::Vector2f Camera::pixelToWorldCoords(sf::Vector2f & position)
{
	 /// as we are using a view we will need to transform 
	 // things such as the mouse position(in pixel coords)
	 // to the world view coordinates to get an accurate depiction of that 
	 // of that position
	return sf::Vector2f(m_window->mapPixelToCoords(sf::Vector2i(position)));


}
 // opposite of above 
 sf::Vector2f Camera::worldToPixelCoords(sf::Vector2f& position)
 {
	 return sf::Vector2f(m_window->mapCoordsToPixel(position));
 }

void Camera::resSize(sf::FloatRect& newView)
{
	
	m_cameraView = m_window->getView();  /// get view

	m_cameraView.setViewport(newView); // resize

	m_window->setView(m_cameraView); // reset

}

void Camera::moveToPos(sf::Vector2f& pos)
{
	m_cameraView = m_window->getView();
	// calc offset
	sf::Vector2f offset = pos - m_cameraView.getCenter(); 
	//apply offset to view
	m_cameraView.move(offset);

	m_window->setView(m_cameraView); // reset view


}

sf::View& Camera::getView()
{
	return m_cameraView;
}




/**
 * @file main.cpp
 * @author [Jethro Shell]
 * @date [01/03/2025]
 */

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "SceneManager.h"
 /**
  * The main function, which sets up and runs the SFML application.
  *
  * @return 0 if the program finishes successfully
  */
int main() {
    /**
     * Create a new window with a title of "SFML works!" and dimensions of 800x600 pixels.
     */
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    /**
     * Create a new rectangle shape with dimensions of 100x100 pixels.
     */
    sf::RectangleShape rectangle(sf::Vector2f(100, 100));

    /**
     * Set the fill color of the rectangle to green.
     */
    rectangle.setFillColor(sf::Color::Green);

    /**
     * Position the rectangle at (100, 100) on the screen.
     */
    rectangle.setPosition(100, 100);

    /**
     * Set the target frame rate for the application.
     */
    float f_fps = 60.0f;

    /**
     * Create a clock object to measure time.
     */
    sf::Clock clock;

    /**
     * Get the initial time since the last frame was drawn.
     */
    sf::Time time = clock.restart();

    /**
     * Calculate the target time per frame based on the desired frame rate.
     */
    sf::Time timePerFrame = sf::seconds(1.0f / f_fps);

    
    SceneManager sceneManager = SceneManager(&window,window.getSize().x,window.getSize().y);
    sf::Clock elapsed;
    float dt;
    float lastTime = 0;
    sf::Text displayfps; 
    std::string fpsstring;
    displayfps.setFillColor(sf::Color::Blue);
    displayfps.setScale(1.0f, 1.0f); 
  
    displayfps.setPosition(0.0f, 0.0f);
    while (window.isOpen()) {

        dt = elapsed.restart().asSeconds();
        

        // Poll for events in the window
        sf::Event event;
       

        // Clear the window and draw the rectangle
        window.clear();
       /* window.draw(rectangle);*/ 
        sceneManager.draw();
        window.display();
        sceneManager.update(dt,event);
    }

    return 0;
}
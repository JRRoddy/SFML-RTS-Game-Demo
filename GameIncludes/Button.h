#pragma once

#include "SFML/Graphics.hpp"
#include "iostream"



class Button {

public:
    Button(sf::Vector2f size, std::string displayText, unsigned int charSize)
    {
        m_buttonSize = size;
        m_displayTextCharacterSize = charSize;
        m_displayText.setCharacterSize(m_displayTextCharacterSize);
        m_displayText.setString(displayText);
        m_buttonShape = sf::RectangleShape(m_buttonSize);
        m_buttonShape.setOrigin(size / 2.0f);
        m_displayText.setOrigin(sf::Vector2f(m_displayTextCharacterSize, m_displayTextCharacterSize) / 2.0f);


    }
    Button() {};
    ~Button() {};
    void setPosition(sf::Vector2f& position)
    {
        m_buttonShape.setPosition(position);

        /*m_displayText.setPosition(static_cast<float>(m_buttonShape.getPosition().x -m_displayTextCharacterSize),
                                  static_cast<float>(m_buttonShape.getPosition().y - m_displayTextCharacterSize));*/
    }
    void draw(sf::RenderWindow* window)
    {
        window->draw(m_buttonShape);
        window->draw(m_displayText);

    }
    
    template<class menuActionType >
    void addBinding(void (menuActionType::* m_action)()) {
       
    }
    
    void setTextString(std::string& displayText)
    {
        m_displayText.setString(displayText);

    }
    void setTextPos(sf::Vector2f& position)
    {
        m_displayText.setPosition(position);
    }

    void setButtonId(std::string& buttonId)
    {
        m_buttonId = buttonId;
    }
    std::string getButtonId()
    {
        return m_buttonId;
    }
    void setLinkedMenuId(std::string linkedSubMenuId)
    {
        m_linkedMenuId = linkedSubMenuId;
    }
    sf::Text* getTextRef()
    {
        return &m_displayText;
    }
    sf::Vector2f getTextPosition()
    {
        return m_displayText.getPosition();
    }
    std::string getLinkedMenuId()
    {
        return m_linkedMenuId;
    }
    sf::RectangleShape& getShape() {
        return m_buttonShape;
    };
    void setFont(std::string& fontFile)
    {
        m_fontPath = fontFile;
        if (!m_displayFont.loadFromFile(m_fontPath)) std::cout << "could not load button font " << fontFile << std::endl;
        m_displayText.setFont(m_displayFont);
    }
    void setBackgroundColour(sf::Color& colour)
    {
        m_backgroundColour = colour;
        m_buttonShape.setFillColor(m_backgroundColour);
    }
    void setTextColour(sf::Color& colour)
    {
        m_textColour = colour;
        m_displayText.setFillColor(m_textColour);
    }
private:
    std::string m_fontPath;
    sf::Color m_textColour; 
    sf::Color m_backgroundColour;
    sf::RectangleShape m_buttonShape;
    sf::Vector2f m_buttonSize; 
    sf::Text m_displayText; 
    sf::Font m_displayFont; 
    std::string m_linkedMenuId;
    std::string m_buttonId;
    unsigned int m_displayTextCharacterSize = 0;
    

};
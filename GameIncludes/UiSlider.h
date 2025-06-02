#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"

// basic ui slider class that can be used to set things such as voolume using an interpolated value that is returned from the slider 
class UiSlider {
public:
	UiSlider() {};
	UiSlider(float startPercentage, sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColour, float indicatorRadi, sf::Color indicatorColour);
	~UiSlider(){};
	void setIndicatorRadiColour(sf::Color& colour);
	sf::FloatRect  getIndicatorContainerBounds();
	void interpolateIndicatorPosX(float percentage);
	void interpolateIndicatorPosX(sf::Vector2f position);
	void setSliderValue();
	sf::RectangleShape getBounds();
	void interpolateSliderXPos();
	void draw(sf::RenderWindow* window);
	float getSliderEndX();
	float getInterpolater() const;
	sf::Vector2f getPosition();
	void setElementId(std::string& elementId); 
	sf::Vector2f getSliderIndicatorPos();
	void addText(sf::Font & font, std::string& textString, sf::Color & textColour, unsigned int &charSize, float & textPadding);
	std::string getElementId();

private:
	sf::Text m_sliderText;
	sf::RectangleShape m_sliderBackGround;
	sf::CircleShape m_sliderIndicator;
	sf::Vector2f m_position; 
	std::string m_elementId;
	sf::Color m_indcatorColour;
	float m_indicatorRadi = 0.0f;
	float m_interpolater = 0.0f;


};
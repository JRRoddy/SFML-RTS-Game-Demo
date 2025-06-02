#include "UiSlider.h "


UiSlider::UiSlider(float startPercentage, sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColour, float indicatorRadi, sf::Color indicatorColour) {

	m_interpolater = startPercentage;
	m_position = position;
	m_indicatorRadi = indicatorRadi;
	m_indcatorColour = indicatorColour;
	m_sliderBackGround.setSize(size);
	m_sliderBackGround.setOrigin(size / 2.0f);
	m_sliderBackGround.setFillColor(backgroundColour);
	m_sliderBackGround.setPosition(m_position);
	std::cout << "slider position " << m_sliderBackGround.getPosition().x << std::endl;
	m_sliderIndicator.setRadius(m_indicatorRadi);
	m_sliderIndicator.setOrigin(sf::Vector2f(m_indicatorRadi, m_indicatorRadi) / 2.0f);
	m_sliderIndicator.setFillColor(m_indcatorColour);

	interpolateIndicatorPosX(m_interpolater);

}



void UiSlider::interpolateIndicatorPosX(float percentage) {

	m_interpolater = std::clamp(percentage, 0.0f, 1.0f);
	interpolateSliderXPos();


}

void UiSlider::interpolateIndicatorPosX(sf::Vector2f position)
{   
	// adjust the slider indtcaors position based on a passe in positon such as the mouse pos 
	// and clamp the range so the slider indicator cant go out side of its sf rect container 
	float currentX =  (std::clamp(position.x, m_sliderBackGround.getGlobalBounds().left, getSliderEndX()));

	// set the slider indicator's position based on the clamped x value(calculated above) for the position passed in 
	m_sliderIndicator.setPosition(currentX, m_sliderBackGround.getPosition().y - m_indicatorRadi / 2.0f);
	
	// used to find the current t that will be used for getting the interpolated value of the slider 
	// first we subtract the x of the position we passed in from the start point of the 
	// slider's rect container giving us the difference between the two 
	float currentXDiff = position.x -  m_sliderBackGround.getGlobalBounds().left;
	// get full difference between start point and end point of the rect container for the slider 
	float fullDiff = getSliderEndX() - m_sliderBackGround.getGlobalBounds().left;

	// get the percentage that represents how far along the position was across the full slider container 
	// by dividing the current difference between the passed in position and the start point 
	// for the rect container by the full difference between the start point and end point
	// ensure to clamp between 0 and 1 for percent slider value 
	m_interpolater = std::clamp(currentXDiff / fullDiff,0.0f,1.0f);

	std::cout << m_interpolater << std::endl;

}

void UiSlider::setSliderValue()
{
	m_interpolater = std::clamp(m_sliderIndicator.getPosition().x / getSliderEndX(),0.0f,1.0f);
	
}

sf::RectangleShape UiSlider::getBounds(){

	return m_sliderBackGround;

}

void UiSlider::interpolateSliderXPos()
{
	// get the start and end values based on width and height of slider 
	float startX = m_sliderBackGround.getGlobalBounds().left;
	float endX = getSliderEndX();
	// add to the beggining of the slider(top left corner of sf rect) the percentage of the 
	// differnce that is caluclated by subtracting the end position for the slider's rectangle 
	// from the start and multiplying by a percentage modifier 
	float interpX = startX + (endX - startX) * m_interpolater;
	// set the slider indicators position to the new interpolated x position along the 
    // slider's background rectangle container 
	m_sliderIndicator.setPosition(sf::Vector2f(interpX, m_sliderBackGround.getPosition().y  - m_indicatorRadi/2.0f));

}

void UiSlider::draw(sf::RenderWindow* window)
{
	// draw slider indicator and its background sf rect container 
	window->draw(m_sliderBackGround);
	window->draw(m_sliderIndicator);
	window->draw(m_sliderText);

}

float UiSlider::getSliderEndX()
{ 

	// get the end point of the slider's background end container used for interpolation 
	return m_sliderBackGround.getGlobalBounds().left + m_sliderBackGround.getGlobalBounds().width;
}

float UiSlider::getInterpolater() const
{
	return m_interpolater;
}

sf::Vector2f UiSlider::getPosition()
{
	return m_position;
}

void UiSlider::setElementId(std::string& elementId)
{
	m_elementId = elementId;
}

sf::Vector2f UiSlider::getSliderIndicatorPos()
{
	return m_sliderIndicator.getPosition();
}

void UiSlider::addText(sf::Font& font, std::string& textString, sf::Color& textColour, unsigned int& charSize, float & textPadding)
{
	m_sliderText.setCharacterSize(charSize); 
	m_sliderText.setFont(font); 
	m_sliderText.setString(textString); 
	m_sliderText.setColor(textColour);
	m_sliderText.setOrigin(m_sliderText.getGlobalBounds().getSize()/2.0f + m_sliderText.getLocalBounds().getPosition());

	sf::Vector2f leftPos = sf::Vector2f( (m_sliderBackGround.getPosition().x -m_sliderBackGround.getSize().x / 2.0f)-textPadding,m_sliderBackGround.getPosition().y );
    
	leftPos -= sf::Vector2f(m_sliderText.getGlobalBounds().getSize().x / 2.0f , 0.0f);

	m_sliderText.setPosition(leftPos);
	 



}



std::string UiSlider::getElementId()
{
	return m_elementId;
}





void UiSlider::setIndicatorRadiColour(sf::Color& colour) {
	m_sliderIndicator.setFillColor(colour);
}

sf::FloatRect UiSlider::getIndicatorContainerBounds()
{
	return m_sliderBackGround.getGlobalBounds();
}


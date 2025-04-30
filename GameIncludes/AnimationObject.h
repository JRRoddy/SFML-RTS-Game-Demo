#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
// object used to describe a singlaur animation 
// and play/reset that animation
class AnimationObject {
	
public:
	AnimationObject() {};
	AnimationObject(std::shared_ptr<std::vector<sf::Sprite>> frames,std::shared_ptr<sf::Sprite> &baseSpriteReference,float &delay);
	~AnimationObject() {};
	bool animEndNoWait();
	bool animAtEnd();
	const sf::Texture * getAnimTexture();
	AnimationObject(const AnimationObject& other);
	AnimationObject operator = (const AnimationObject& other);
	AnimationObject(AnimationObject* animToCopy);
	std::shared_ptr<std::vector<sf::Sprite>> & getframes();
	void setBaseSpirteRef(sf::Sprite* sprite);

	void play(); 
	void reset();
	void setFrameDelay(float & miliDelay);
	sf::Time &getFrameDelay();
	sf::Sprite* getSpriteRef(); 
	int getCurrentFrameIndex();
	void setFrames(std::shared_ptr<std::vector<sf::Sprite>>& frames);
private:
	sf::Sprite* m_baseSpriteRef = nullptr; 
	std::shared_ptr<std::vector<sf::Sprite>> m_frames;
	sf::Clock m_frameTimer;
	sf::Time m_frameDelay;
	int m_currentFrameIndex = 0;

	


};
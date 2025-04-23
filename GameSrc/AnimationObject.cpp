#include "AnimationObject.h"

AnimationObject::AnimationObject(std::vector<std::shared_ptr<sf::Sprite>> frames, std::shared_ptr<sf::Sprite> &baseSpriteReference, float & miliDelay)
{
	m_frames = frames; // sprite frames for animation
	m_frameDelay = sf::milliseconds(miliDelay); // delay between frames
	m_baseSpriteRef = baseSpriteReference.get(); // sprite to animate
	m_currentFrameIndex = 0;// current index into frames vector
}


bool AnimationObject::animAtEnd()
{
	// if we reached end of animation
	return m_currentFrameIndex == m_frames.size()-1;
}

const sf::Texture* AnimationObject::getAnimTexture()
{
	if (m_frames.size()) {
		return m_frames[0].get()->getTexture();
	}
	std::cout<< "animation object sprite frames not set" << std::endl;
	return nullptr;
}
// copy constructor 
AnimationObject::AnimationObject(const AnimationObject& other)
{
	this->m_baseSpriteRef = other.m_baseSpriteRef;
	this->m_frames = other.m_frames;
	this->m_currentFrameIndex = other.m_currentFrameIndex;
	this->m_frameDelay = other.m_frameDelay;
	
}
// copy constructor 
AnimationObject AnimationObject::operator=(const AnimationObject& other)
{
	this->m_baseSpriteRef = other.m_baseSpriteRef;
	this->m_frames = other.m_frames;
	this->m_currentFrameIndex = other.m_currentFrameIndex;
	this->m_frameDelay = other.m_frameDelay;

	return *this;
}





AnimationObject::AnimationObject(AnimationObject* animToCopy)
{
	this->m_frameDelay = animToCopy->m_frameDelay; 
	this->m_frames = animToCopy->m_frames;
	this->m_frameDelay = animToCopy->getFrameDelay(); 
	this->m_currentFrameIndex = animToCopy->getCurrentFrameIndex();
	
}

std::vector<std::shared_ptr<sf::Sprite>>& AnimationObject::getframes()
{
	return m_frames;
}

void AnimationObject::setBaseSpirteRef(sf::Sprite* sprite)
{

	m_baseSpriteRef = sprite;
	std::cout << "animation object base sprite set" << m_baseSpriteRef << std::endl;

}

void AnimationObject::play()
{ 
	// set up the sprite to animate for the frame 
	m_baseSpriteRef->setTexture(*getAnimTexture()); // set the texture to the texture being used by this anim
	// set correct texture rect according to current frame index
	m_baseSpriteRef->setTextureRect(m_frames[m_currentFrameIndex]->getTextureRect()); 
	// set origin according to current frame index
	m_baseSpriteRef->setOrigin(m_frames[m_currentFrameIndex]->getOrigin());
	// if we have reached our frame delay
	if (m_frameTimer.getElapsedTime().asMilliseconds() >= m_frameDelay.asMilliseconds()) {
		// cycle to next frame and reset timer
		m_currentFrameIndex = (++m_currentFrameIndex) % m_frames.size();
		m_frameTimer.restart();
	}

}

void AnimationObject::reset()
{
	m_currentFrameIndex = 0;
	m_frameTimer.restart();

}

void AnimationObject::setFrameDelay(float& miliDelay)
{
	m_frameDelay = sf::milliseconds(miliDelay);

}

sf::Time& AnimationObject::getFrameDelay()
{
	return m_frameDelay;
}



sf::Sprite* AnimationObject::getSpriteRef()
{
	return m_baseSpriteRef;
}

int AnimationObject::getCurrentFrameIndex()
{
	return m_currentFrameIndex;
}

void AnimationObject::setFrames(std::vector<std::shared_ptr<sf::Sprite>>& frames)
{
	m_frames = frames;
}

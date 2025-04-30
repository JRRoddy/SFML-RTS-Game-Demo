#include "StatusEffect.h"


bool StatusEffect::durationFinished()
{

   return m_durationTimer.getElapsedTime().asSeconds() >= m_endTime.asSeconds();

}

void StatusEffect::setInitiater(Character* character)
{
    m_initiater = character;
}

void StatusEffect::activate()
{  
    m_isActive = true;
    m_endTime = sf::seconds(m_duration);
    m_durationTimer.restart(); 

}

void StatusEffect::reset()
{
    m_initiater = nullptr; 
    m_durationTimer.restart();
}



float StatusEffect::getDuration() const
{
    return m_duration;
}

bool StatusEffect::hasDuration() const
{
    return m_hasDuration;
}

bool StatusEffect::getIsActive()const
{
    return m_isActive;
}

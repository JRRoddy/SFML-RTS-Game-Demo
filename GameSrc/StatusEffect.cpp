#include "StatusEffect.h"


void StatusEffect::clone(StatusEffect* copy)
{
    copy->setDuration(m_duration);
    
}



bool StatusEffect::durationFinished()
{

   return m_durationTimer.getElapsedTime().asSeconds() >= m_endTime.asSeconds();

}

void StatusEffect::setInitiater(characterStats* statsForInitiater)
{
    m_initiaterStats = statsForInitiater;
}

void StatusEffect::activate()
{  
    m_isActive = true;
    m_endTime = sf::seconds(m_duration);
    m_durationTimer.restart(); 

}

void StatusEffect::reset()
{
    m_initiaterStats = nullptr; 
    m_durationTimer.restart();
    m_isActive = false;
}


float StatusEffect::getDuration() const
{
    return m_duration;
}

void StatusEffect::setDuration(float& duration)
{
    m_duration = duration; 
    m_endTime = sf::seconds(duration);
}

void StatusEffect::setStatusEffectId(StatusEffectIds id)
{
    m_statusEffectId = id;
}

StatusEffectIds StatusEffect::getStatusEffectId()
{
    return m_statusEffectId;
}

bool StatusEffect::hasDuration() const
{
    return m_hasDuration;
}

bool StatusEffect::getIsActive()const
{
    return m_isActive;
}

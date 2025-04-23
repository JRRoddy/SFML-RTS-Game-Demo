#include "Goblin.h"

// goblin contructor setting data for this specifc enemy 
// that will then be used by various methods in parent classes
Goblin::Goblin()
{
    m_damage = 10.0f;
    m_health = 30.0f; 
    m_speed = 200.0f;  
    m_idleAnimPath = "../Assets/Animations/GoblinIdle.png";
    m_runAnimPath = "../Assets/Animations/goblinRunAnim.png";
    m_attackAnimPath = "../Assets/Animations/GoblinAttackAnim.png";
    m_runAnimDelay = 70.0f;
    m_idleAnimDelay = 70.0f; 
    m_attackAnimDelay = 70.0f; 
    m_spawnCap = 10;
    m_debugCircle.setFillColor(sf::Color::Red); 
    m_debugCircle.setRadius(5.0f); 
    m_debugCircle.setOrigin(5.0f / 2.0f, 5.0f / 2.0f); 
    

   
}

EnemyBase* Goblin::clone()
{
    Goblin* copy = new Goblin(); 
    EnemyBase::clone(copy); 
    return copy;
    
}



void Goblin::update(float dt)
{
    
    flipSpriteX(m_direction.x); 
   
    setAnimStates();
    m_animationController.get()->update();
    updatePosition(dt);
    m_debugCircle.setPosition(m_position);

}

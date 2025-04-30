#include "Goblin.h"

// goblin contructor setting data for this specifc enemy 
// that will then be used by various methods in parent classes
Goblin::Goblin()
{
    m_damage = 0.0f;
    m_baseHealth = 40.0f;
    m_health = 40.0f; 
    m_speed = 200.0f;  
    m_idleAnimPath = "../Assets/Animations/GoblinIdle.png";
    m_runAnimPath = "../Assets/Animations/goblinRunAnim.png";
    m_attackAnimPath = "../Assets/Animations/GoblinAttackAnim.png";
    m_deathAnimPath = "../Assets/Animations/EnemyDeathAnim.png";
    m_runAnimDelay = 70.0f;
    m_idleAnimDelay = 70.0f; 
    m_attackAnimDelay = 80.0f; 
    m_deathAnimDelay = 85.0f;
    m_spawnCap = 1;
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




#pragma once
#include "StatusEffect.h"
// the taunt status effect inherits from the status effect class 
// this status effect if it can be applied will force a character
// to target another when attacking
class TauntStatusEffect:public StatusEffect {

public:
    TauntStatusEffect();
    ~TauntStatusEffect() {
        std::cout << "taunt status effect destructor called" << std::endl;
    }; 
    bool finished();
    bool canApply();
    void effect(characterStats* character);


private:



};


#pragma once
#include "StatusEffect.h"

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


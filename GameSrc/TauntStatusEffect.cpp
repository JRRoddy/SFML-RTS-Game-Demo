#include "TauntStatusEffect.h"

TauntStatusEffect::TauntStatusEffect() {

    m_hasDuration = false;

}


bool TauntStatusEffect::finished()
{
    
    return m_initiaterStats->health<=0.0f  ;
}

bool TauntStatusEffect::canApply()
{
    return m_initiaterStats == nullptr;
}

void TauntStatusEffect::effect(characterStats* character)
{
    


}

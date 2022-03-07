#include "lightTank.h"


bool LightTank::IsAvailableForShoot(Vehicle *enemy) {
    if (hasABonus){
        int d = this->GetCurrentPosition().Distance(enemy->GetCurrentPosition());
        return d == 1 || d == 2;
    }
    return this->GetCurrentPosition().Distance(enemy->GetCurrentPosition()) == 2;
}

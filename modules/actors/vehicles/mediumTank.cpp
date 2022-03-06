#include "mediumTank.h"


bool MediumTank::IsAvailableForShoot(Vehicle *enemy) {
    return this->GetCurrentPosition().Distance(enemy->GetCurrentPosition()) == 2;
}



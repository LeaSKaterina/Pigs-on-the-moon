#include "lightTank.h"


bool LightTank::IsAvailableForShoot(Vehicle *enemy) {
    return Hex::GetDistance(this->GetCurrentPosition(), enemy->GetCurrentPosition()) == 2;
}


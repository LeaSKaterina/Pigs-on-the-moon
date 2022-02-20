#include "lightTank.h"


bool LightTank::IsAvailableForShoot(Vehicle *enemy) {
    return this->GetCurrentPosition().Distance(enemy->GetCurrentPosition()) == 2;
}

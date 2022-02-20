#include "heavyTank.h"


bool HeavyTank::IsAvailableForShoot(Vehicle *enemy) {
    int d = this->GetCurrentPosition().Distance(enemy->GetCurrentPosition());
    return d == 1 || d == 2;
}

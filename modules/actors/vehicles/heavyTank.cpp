#include "heavyTank.h"

bool HeavyTank::IsAvailableForShoot(Vehicle *enemy) {
    int d = Hex::GetDistance(this->GetCurrentPosition(), enemy->GetCurrentPosition());
    return d == 1 || d == 2;
}
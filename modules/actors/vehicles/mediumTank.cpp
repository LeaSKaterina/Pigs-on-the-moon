#include "mediumTank.h"

bool MediumTank::IsAvailableForShoot(Vehicle *enemy) {
    return Hex::GetDistance(this->GetCurrentPosition(), enemy->GetCurrentPosition()) == 2;
}
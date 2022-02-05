#include "spg.h"


bool Spg::IsAvailableForShoot(Vehicle *enemy) {
    return Hex::GetDistance(this->GetCurrentPosition(), enemy->GetCurrentPosition()) == 3;
}
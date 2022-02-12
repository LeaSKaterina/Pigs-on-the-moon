#include "spg.h"


bool Spg::IsAvailableForShoot(Vehicle *enemy) {
    return this->GetCurrentPosition().Distance(enemy->GetCurrentPosition()) == 3;
}
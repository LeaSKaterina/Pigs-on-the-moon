#include "spg.h"


bool Spg::IsAvailableForShoot(Vehicle *enemy) {
    if (hasABonus) {
        int d = this->GetCurrentPosition().Distance(enemy->GetCurrentPosition());
        return d == 4 || d == 3;
    }
    return this->GetCurrentPosition().Distance(enemy->GetCurrentPosition()) == 3;
}

#include "atSpg.h"

using namespace std;


bool AtSpg::IsAvailableForShoot(Vehicle *enemy) {
    int d = this->GetCurrentPosition().Distance(enemy->GetCurrentPosition());
    if (d > 3)
        return false;

    return ((this->GetCurrentPosition().x == enemy->GetCurrentPosition().x) ||
            (this->GetCurrentPosition().y == enemy->GetCurrentPosition().y) ||
            (this->GetCurrentPosition().z == enemy->GetCurrentPosition().z));
}

Point3D AtSpg::Shoot(Vehicle *enemy) {

    const auto &[ x, y, z] = this->GetCurrentPosition();
    const auto &[enemyX, enemyY, enemyZ] = enemy->GetCurrentPosition();

    if (x == enemyX) {
        if (y > enemyY) {
            return {x, y - 1, z + 1};
        } else {
            return {x, y + 1, z - 1};
        }
    }
    if (y == enemyY) {
        if (x > enemyX) {
            return {x - 1, y, z + 1};
        } else {
            return {x + 1, y, z - 1};
        }
    }
    if (z == enemyZ) {
        if (x > enemyX) {
            return {x - 1, y + 1, z};
        } else {
            return {x + 1, y - 1, z};
        }
    }
    return {0, 0, 0};
}

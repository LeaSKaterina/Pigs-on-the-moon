#include "atSpg.h"

using namespace std;


bool AtSpg::IsAvailableForShoot(Vehicle *enemy) {
    int d = Hex::GetDistance(this->GetCurrentPosition(), enemy->GetCurrentPosition());
    if (d == 1)
        return true;
    if (d > 3)
        return false;

    return (get<0>(this->GetCurrentPosition()) == get<0>(enemy->GetCurrentPosition()) ||
            get<1>(this->GetCurrentPosition()) == get<1>(enemy->GetCurrentPosition()) ||
            get<2>(this->GetCurrentPosition()) == get<2>(enemy->GetCurrentPosition()));
}

Point AtSpg::Shoot(Vehicle *enemy) {

    const auto &[x, y, z] = this->GetCurrentPosition();
    const auto &[enemyX, enemyY, enemyZ] = enemy->GetCurrentPosition();

    if (x == enemyX) {
        if (y > enemyY) {
            return make_tuple(x, y - 1, z + 1);
        } else {
            return make_tuple(x, y + 1, z - 1);
        }
    }
    if (y == enemyY) {
        if (x > enemyX) {
            return make_tuple(x - 1, y, z + 1);
        } else {
            return make_tuple(x + 1, y, z - 1);
        }
    }
    if (z == enemyZ) {
        if (x > enemyX) {
            return make_tuple(x - 1, y + 1, z);
        } else {
            return make_tuple(x + 1, y - 1, z);
        }
    }
    return make_tuple(0, 0, 0);
}

#include "atSpg.h"

using namespace std;


bool AtSpg::IsAvailableToShoot(const Point3D &point3D) {
    int d = this->GetCurrentPosition().Distance(point3D);
    if ((d > 4) || (d > 3 && !hasABonus))
        return false;

    return ((this->GetCurrentPosition().x == point3D.x) ||
            (this->GetCurrentPosition().y == point3D.y) ||
            (this->GetCurrentPosition().z == point3D.z));
}

Point3D AtSpg::Shoot(Vehicle &enemy) {

    const auto &[x, y, z] = this->GetCurrentPosition();
    const auto &[enemyX, enemyY, enemyZ] = enemy.GetCurrentPosition();

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

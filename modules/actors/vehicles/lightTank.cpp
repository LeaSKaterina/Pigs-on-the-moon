#include "lightTank.h"


bool LightTank::IsAvailableToShoot(const Point3D &point3D) {
    if (hasABonus) {
        int d = this->GetCurrentPosition().Distance(point3D);
        return d == 1 || d == 2;
    }
    return this->GetCurrentPosition().Distance(point3D) == 2;
}

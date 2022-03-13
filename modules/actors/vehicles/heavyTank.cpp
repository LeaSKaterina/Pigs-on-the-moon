#include "heavyTank.h"


bool HeavyTank::IsAvailableToShoot(const Point3D &point3D) {
    int d = this->GetCurrentPosition().Distance(point3D);
    return d == 1 || d == 2;
}

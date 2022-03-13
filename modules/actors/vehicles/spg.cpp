#include "spg.h"


bool Spg::IsAvailableToShoot(const Point3D &point3D) {
    if (hasABonus) {
        int d = this->GetCurrentPosition().Distance(point3D);
        return d == 4 || d == 3;
    }
    return this->GetCurrentPosition().Distance(point3D) == 3;
}

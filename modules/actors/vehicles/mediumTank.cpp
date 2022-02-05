#include "mediumTank.h"

std::vector<Point> MediumTank::GetAvailableMovePoints(Point target, int r) {
    std::vector<Point> res;
    return res;
}

bool MediumTank::IsAvailableForShoot(Vehicle *enemy) {
    return Hex::GetDistance(this->GetCurrentPosition(), enemy->GetCurrentPosition()) == 2;
}
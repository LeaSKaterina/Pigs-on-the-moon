#include "heavyTank.h"

std::vector<Point> HeavyTank::GetAvailableMovePoints(Point target, int r) {
    std::vector<Point> res;
    return res;
}

bool HeavyTank::IsAvailableForShoot(Vehicle *enemy) {
    int d = Hex::GetDistance(this->GetCurrentPosition(), enemy->GetCurrentPosition());
    return d == 1 || d == 2;
}
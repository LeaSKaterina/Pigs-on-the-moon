#include "atSpg.h"
using namespace std;

vector<Point> AtSpg::GetAvailableMovePoints(Point target, int r) {
    vector<Point> res;
    return res;
}
bool AtSpg::IsAvailableForShoot(Vehicle *enemy) {
    int d = Hex::GetDistance(this->GetCurrentPosition(), enemy->GetCurrentPosition());
    if (d == 1)
        return true;
    if (d > 3)
        return false;

    vector<Point> ring = move(Hex::GetRing(this->GetCurrentPosition(), d));
    for (int i = 0; i < 6; i++) {
        if (enemy->GetCurrentPosition() == ring[i])
            return true;
    }
    return false;
}
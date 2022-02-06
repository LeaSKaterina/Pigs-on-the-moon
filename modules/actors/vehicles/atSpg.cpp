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

#include "vehicle.h"


bool Vehicle::Move(Hex *newPos) {
    if (!newPos->Occupy())
        return false;

    currentPosition->Free();
    currentPosition = newPos;
    return true;
}

void Vehicle::Update(int hp, Hex *newPos, int capture) {
    if (currentPosition)
        currentPosition->Free();
    currentPosition = newPos;
    currentPosition->Occupy();
    health = hp;
    capturePoints = capture;
}

void Vehicle::Respawn() {
    Move(spawnPosition);
    health = destructionPoints;
    capturePoints = 0;
}

int Vehicle::GetHit(int hp) {
    this->health -= hp;
    if (health <= 0)
        return destructionPoints;
    return 0;
}

//minPath = currentPosition -> neighbor -> neighbor -> ...
//return index
int Vehicle::GetAvailableMovePoints(const std::vector<Hex *> &minPath) const {
    return std::min(this->speedPoints, (int) minPath.size() - 1);
}

Point3D Vehicle::Shoot(Vehicle &enemy) {
    if (hasABonus) {
        if (currentPosition->GetType() != ConstructionsTypes::CATAPULT) {
            hasABonus = false;
        }
    }
    return enemy.GetCurrentPosition();
}

#include "vehicle.h"


bool Vehicle::Move(Hex *newPos) {
    if (!newPos->Occupy())
        return false;

    currentPosition->Free();
    currentPosition = newPos;
    return true;
}

void Vehicle::Update(int health, Hex *newPos, int capture) {
    if (currentPosition)
        currentPosition->Free();
    currentPosition = newPos;
    currentPosition->Occupy();
    this->health = health;
    capturePoints = capture;
}

void Vehicle::InitSpawn(Hex *p) {
    spawnPosition = p;
    currentPosition = spawnPosition;
}

void Vehicle::Respawn() {
    Move(spawnPosition);
    health = destructionPoints;
    capturePoints = 0;
}

int Vehicle::GetHit(int damage) {
    this->health -= damage;
    if (health <= 0)
        return destructionPoints;
    return 0;
}

Hex *Vehicle::GetAvailableMovePoint(const std::vector<Hex *> &minPath) {
    for (int i = std::min(this->speedPoints, (int) minPath.size() - 1); i > 0; --i) {
        if (minPath[i]->IsEmpty())
            return minPath[i];
    }
    return nullptr;
}
Point3D Vehicle::Shoot(Vehicle *enemy) {
    if (hasABonus) {
        if (currentPosition->GetType() != ConstructionsTypes::CATAPULT) {
            hasABonus = false;
        }
    }
    return enemy->GetCurrentPosition();
}

//
// Created by HP on 02.02.2022.
//

#include "vehicle.h"

using namespace  VehiclesTypes;

Vehicle::Vehicle(VehiclesTypes::Type type, int playerId) {
    switch (type) {
        case MediumTank:
            health = 2;
            speedPoints = 2;
            break;
        case LightTank:
        case HeavyTank:
        case AtSpg:
        case Spg:
            break;
    }
    destructionPoints = health;
    this->playerId = playerId;
    this->type = type;
}

bool Vehicle::Move(Hex *newPos) {
    if (!newPos->Occupy())
        return false;

    currentPosition->Free();
    currentPosition = newPos;
    return true;
}

int Vehicle::Shoot(Vehicle *v) {// вернет сколько очков заработал
    if (IsEnemy(v))
        return v->GetHit(this->damage);
    return 0;
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

#include "vehicle.h"
#include "..\map\hex.h"

Vehicle::Vehicle(Type type, int playerId) {
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
}

bool Vehicle::Move(Hex *newPos) {
    if (!newPos->Occupy())
        return false;

    currentPosition->Free();
    currentPosition = newPos;
    return true;
}

int Vehicle::Shoot(Vehicle *v) { // вернет сколько очков заработал
    if (IsEnemy(v))
        return v->GetHit(this->Damage);
    return 0;
}

void Vehicle::IncCapture() {
    capturePoints++;
}

void Vehicle::DropCapture() {
    capturePoints = 0;
}

void Vehicle::Update(int health, Hex *newPos, int capture) {
    currentPosition = newPos;
    this->health = health;
    capturePoints = capture;
}

int Vehicle::GetPlayerId() const {
    return playerId;
}

const std::tuple<int, int, int> &Vehicle::GetSpawn() const {
    return spawnPosition->GetCoordinates();
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

int Vehicle::GetHit(int damage = 1) {
    this->health -= damage;
    if (health <= 0)
        return destructionPoints;
    return 0;
}

bool Vehicle::IsEnemy(Vehicle *v) {
    return this->playerId != v->playerId;
}


#include "vehicle.h"

Vehicle::Vehicle(VehiclesTypes::Type type, int playerId) {
    switch (type) {
        case VehiclesTypes::Type::MediumTank:
            health = 2;
            speedPoints = 2;
            break;
        case VehiclesTypes::Type::LightTank:
        case VehiclesTypes::Type::HeavyTank:
        case VehiclesTypes::Type::AtSpg:
        case VehiclesTypes::Type::Spg:
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

int Vehicle::Shoot(Vehicle *v) { // вернет сколько очков заработал
    if (IsEnemy(v))
        return v->GetHit(this->damage);
    return 0;
}

void Vehicle::IncCapture() {
    capturePoints++;
}

void Vehicle::DropCapture() {
    capturePoints = 0;
}

void Vehicle::Update(int health, Hex *newPos, int capture) {
    if (currentPosition)
        currentPosition->Free();
    currentPosition = newPos;
    currentPosition->Occupy();
    this->health = health;
    capturePoints = capture;
}

int Vehicle::GetPlayerId() const {
    return playerId;
}

const std::tuple<int, int, int> &Vehicle::GetSpawn() const {
    return spawnPosition->GetCoordinates();
}

const std::tuple<int, int, int> &Vehicle::GetCurrentPosition() const {
    return currentPosition->GetCoordinates();
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

bool Vehicle::IsEnemy(Vehicle *v) const {
    return this->playerId != v->playerId;
}


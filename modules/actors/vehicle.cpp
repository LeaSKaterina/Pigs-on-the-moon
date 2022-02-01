#include "vehicle.h"

Vehicle::Vehicle(Type type, int playerId) {
    switch (type) {
        case MEDIUM_TANK:
            health = 2;
            speedPoints = 2;
            break;
        case LIGHT_TANK:
        case HEAVY_TANK:
        case AT_SPG:
        case SPG:
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
        return v->GetHit(this->damage);
    return 0;
}

void Vehicle::Update(int health, Hex *newPos, int capture) {
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


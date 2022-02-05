#include "vehicle.h"


bool Vehicle::Move(Hex *newPos) {
    if (!newPos->Occupy())
        return false;

    currentPosition->Free();
    currentPosition = newPos;
    return true;
}

int Vehicle::Shoot(Vehicle *v) { // return points for shooting this tank
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

std::multimap<int, Point> Vehicle::GetAvailableMovePoints(Point target) {
    const Point& center = this->currentPosition->GetCoordinates();
    std::multimap<int, Point> availablePoints;

    for (int i = speedPoints; i > 0; --i) {
        std::vector<Point> ring = Hex::GetRing(center, i);
        for(const Point &point : ring){
            if(Hex::GetDistance(point, Point(0, 0, 0)) < 12) // 12?
                availablePoints.emplace(Hex::GetDistance(point, target), point);
        }
    }

    return availablePoints;
}

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
    health = DESTRUCTION_POINTS;
    capturePoints = 0;
}

int Vehicle::GetHit(int damage) {
    this->health -= damage;
    if (health <= 0)
        return DESTRUCTION_POINTS;
    return 0;

}

std::multimap<int, Point> Vehicle::GetAvailableMovePoints(const Point &target) {
    const Point &center = this->currentPosition->GetCoordinates();
    std::multimap<int, Point> availablePoints;

    for (int i = SPEED_POINTS; i > 0; --i) {
        std::vector<Point> ring = Hex::GetRing(center, i);
        for (const Point &point: ring) {
            if (Hex::GetDistance(point, Point(0, 0, 0)) < 12) // 12?
                availablePoints.emplace(Hex::GetDistance(point, target), point);
        }
    }

    return availablePoints;
}
std::vector<Point> Vehicle::PriorityMoveTriangle(const Point &&target) {
    // 0 1 2
    std::vector<int[3]> to_check(6);
    int current[3] = {
            std::get<0>(this->currentPosition->GetCoordinates()),
            std::get<1>(this->currentPosition->GetCoordinates()),
            std::get<2>(this->currentPosition->GetCoordinates())
    };
    int next = 0;

    // point of two triangles.
    for (int const_coo = 0; const_coo < 3; const_coo++) {
        to_check[next][const_coo] = Hex::GetCooValue(target, const_coo);
        for (int aim_coo = 0; aim_coo < 3; aim_coo++) {
            if (aim_coo == const_coo)
                continue;
            to_check[next][aim_coo] = current[aim_coo];
        }
    }

    // find two valid points.
    std::vector<int> valid_ind; // len will be 2
    for (int i = 0; i < 6; i++) {
        int coo = 0;
        for (; coo < 3; coo++) {
            if (!IsBetweenCoo(
                        to_check[i][coo],
                        Hex::GetCooValue(target, coo),
                        current[coo]))
                break;
        }
        if (coo < 3)
            valid_ind.push_back(i);
    }

    std::vector<Point> triangle_base_points(2);
    for (int i = 0; i < 2; i++) {
        triangle_base_points[i] = std::move(Hex::GetDiagonalVector(current, to_check[valid_ind[i]], SPEED_POINTS));
    }

    return triangle_base_points;
}

bool Vehicle::IsBetweenCoo(int coo, int first, int second) {
    int l, r;
    if (first < second) {
        l = first; r = second;
    }
    else {
        l = second; r = first;
    }
    return coo >= l && coo <= r;
}

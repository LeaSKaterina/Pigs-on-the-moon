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

Hex * Vehicle::GetAvailableMovePoints(const std::vector<Hex *> &minPath) {
    for (int i = std::min(this->speedPoints, (int)minPath.size() - 1); i > 0; --i) {
        if (minPath[i]->IsEmpty())
            return minPath[i];
    }
    return nullptr;
}

std::vector<Point3D> Vehicle::PriorityMoveTriangle(const Point3D &&target) {
    // 0 1 2
    std::vector<int[3]> to_check(6);
//    int current[3] = {
//            std::get<0>(this->currentPosition->GetCoordinates()),
//            std::get<1>(this->currentPosition->GetCoordinates()),
//            std::get<2>(this->currentPosition->GetCoordinates())
//    };
    Point3D current = this->currentPosition->GetCoordinates();
    int next = 0;

    // point of two triangles.
    for (int const_coo = 0; const_coo < 3; const_coo++) {
        to_check[next][const_coo] = target[const_coo];
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
                        target[coo],
                        current[coo]))
                break;
        }
        if (coo < 3)
            valid_ind.push_back(i);
    }

    std::vector<Point3D> triangleBasePoints(2);
    for (int i = 0; i < 2; i++) {
        Point3D checkPoint (to_check[valid_ind[i]][0], to_check[valid_ind[i]][1], to_check[valid_ind[i]][2]);
        triangleBasePoints[i] = Hex::GetDiagonalVector(current, checkPoint, speedPoints);
    }

    return triangleBasePoints;
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


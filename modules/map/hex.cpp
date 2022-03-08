#include "hex.h"

using namespace std;

bool Hex::Occupy() {
    if (!isEmpty)
        return false;

    isEmpty = false;
    return true;
}

vector<Point3D> Hex::GetRing(Point3D center, int r) {
    vector<Point3D> res;
    int pointArr[3]{0, 0, 0};
    const int centerArr[]{center.x, center.y, center.z};

    for (int dr = 0; dr < r; dr++) {
        for (int i = 0; i < 3; i++) {
            pointArr[i % 3] = centerArr[i % 3] + (r - dr);
            pointArr[(i + 1) % 3] = centerArr[(i + 1) % 3] + dr;
            pointArr[(i + 2) % 3] = centerArr[(i + 2) % 3] - r;
            res.emplace_back(pointArr[0], pointArr[1], pointArr[2]);
            pointArr[i % 3] = centerArr[i % 3] - (r - dr);
            pointArr[(i + 1) % 3] = centerArr[(i + 1) % 3] - dr;
            pointArr[(i + 2) % 3] = centerArr[(i + 2) % 3] + r;
            res.emplace_back(pointArr[0], pointArr[1], pointArr[2]);
        }
    }

    return res;
}


Point3D Hex::GetDiagonalVector(const Point3D &from, const Point3D &to, int radius) {
    // find on which coordinate this diagonal is:
    int coo = 0;
    for (; coo < 3; coo++) {
        if (from[coo] == to[coo])
            break;
    }
    if (coo > 3) return Point3D{-1, -1, -1};
    int res[3];
    for (int i = 0; i < 3; i++) {
        if (i == coo)
            res[i] = from[i];
        else {
            int direction = to[i] > 0 ? 1 : -1;
            res[i] = from[i] + radius * direction;
        }
    }
    return {res[0], res[1], res[2]};
}

ConstructionsTypes::Type Hex::GetType() const {
    return ownerId == -1 ? ConstructionsTypes::Type::EMPTY : (ConstructionsTypes::Type) ownerId;
}

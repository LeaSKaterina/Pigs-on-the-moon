#include "hex.h"
using namespace std;

bool Hex::Occupy() {
    if (!isEmpty)
        return false;

    isEmpty = false;
    return true;
}

int Hex::GetDistance(const Point &f, const Point &s) {
    auto &[x1, y1, z1] = f;
    auto &[x2, y2, z2] = s;
    return (abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)) / 2;
}

vector<Point> Hex::GetRing(Point center, int r) {
    vector<Point> res;
    int pointArr[3]{0, 0, 0};
    int centerArr[3]{0, 0, 0};
    centerArr[0] = get<0>(center);
    centerArr[1] = get<1>(center);
    centerArr[2] = get<2>(center);

    for (int dr = 0; dr < r; dr++) {
        for (int i = 0; i < 3; i++) {
            pointArr[i % 3] = centerArr[i % 3] + (r - dr);
            pointArr[(i + 1) % 3] = centerArr[(i + 1) % 3] + dr;
            pointArr[(i + 2) % 3] = centerArr[(i + 2) % 3] - r;
            res.push_back(make_tuple(pointArr[0], pointArr[1], pointArr[2]));
            pointArr[i % 3] = centerArr[i % 3] - (r - dr);
            pointArr[(i + 1) % 3] = centerArr[(i + 1) % 3] - dr;
            pointArr[(i + 2) % 3] = centerArr[(i + 2) % 3] + r;
            res.push_back(make_tuple(pointArr[0], pointArr[1], pointArr[2]));
        }
    }

    return res;
}
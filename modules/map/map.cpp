#include "map.h"

using namespace std;

void Map::AddBase(vector<Point> &points) {
    vector<Hex *> basis(points.size());
    for (int i = 0; i < points.size(); i++) {
        basis[i] = grid[points[i]];
    }
    content.push_back(new Base(basis));
}

void Map::InitGrid() {
    for (int x = -size + 1; x < size; x++) {
        for (int y = -size + 1; y < size; y++) {
            int z = -x - y;
            if (x + y + z == 0 && abs(z) < size)
                grid[make_tuple(x, y, z)] = new Hex(x, y, z);
        }
    }
}

vector<Point> Map::GetRing(Point center, int r) {
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


Map::~Map() {
    for (auto &[k, h] : grid) {
        delete h;
    }

    for (auto c : content)
        delete c;
}

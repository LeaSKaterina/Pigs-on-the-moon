#include "map.h"

void Map::AddBase(std::vector<Point> &points) {
    std::vector<Hex *> basis;
    for (auto &p : points) {
        basis.push_back(grid[p]);
    }
    content.push_back(new Base(basis));
}

void Map::InitGrid() {
    for (int x = -size + 1; x < size; x++) {
        for (int y = -size + 1; y < size; y++) {
            for (int z = 1 - size; z < size; z++) {
                if (x + y + z == 0)
                    grid[std::make_tuple(x, y, z)] = new Hex(x, y, z);
            }
        }
    }
}

std::vector<Point> Map::GetRing(Point center, int r) {
    std::vector<Point> res;
    int pointArr[3]{0, 0, 0};
    int centerArr[3]{0, 0, 0};
    centerArr[0] = std::get<0>(center);
    centerArr[1] = std::get<1>(center);
    centerArr[2] = std::get<2>(center);

    for (int dr = 0; dr < r; dr++) {
        for (int i = 0; i < 3; i++) {
            pointArr[i % 3] = centerArr[i % 3] + (r - dr);
            pointArr[(i + 1) % 3] = centerArr[(i + 1) % 3] + dr;
            pointArr[(i + 2) % 3] = centerArr[(i + 2) % 3] - r;
            res.push_back(std::make_tuple(pointArr[0], pointArr[1], pointArr[2]));
            pointArr[i % 3] = centerArr[i % 3] - (r - dr);
            pointArr[(i + 1) % 3] = centerArr[(i + 1) % 3] - dr;
            pointArr[(i + 2) % 3] = centerArr[(i + 2) % 3] + r;
            res.push_back(std::make_tuple(pointArr[0], pointArr[1], pointArr[2]));
        }
    }

    return res;
}

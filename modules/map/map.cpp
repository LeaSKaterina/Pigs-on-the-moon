#include "map.h"

void Map::AddBase(vector <tuple<int, int, int>> &points) {
    vector < Hex * > basis;
    for (auto &p: points) {
        basis.push_back(grid[p]);
    }
    content.push_back(new Base(basis));
}

void Map::InitGrid() {
    for (int x = -size + 1; x < size; x++) {
        for (int y = -size + 1; y < size; y++) {
            for (int z = 1 - size; z < size; z++) {
                if (x + y + z == 0)
                    grid[make_tuple(x, y, z)] = new Hex(x, y, z);
            }
        }
    }
}


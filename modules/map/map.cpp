#include "map.h"

using namespace std;

void Map::InitGrid() {
    for (int x = -size + 1; x < size; x++) {
        for (int y = -size + 1; y < size; y++) {
            int z = -x - y;
            if (x + y + z == 0 && abs(z) < size)
                grid[{x, y, z}] = new Hex(x, y, z);
        }
    }
}

Map::~Map() {
    for (auto &[k, h]: grid) {
        delete h;
    }

    for (auto c: content)
        delete c;
}

bool Map::IsBasePoint(const Hex *point) const {
    return false;
}

bool Map::IsBasePoint(const Point3D &point) const {
    // TODO!
    return this->Get(point)->IsSpecial();
}
void Map::AddConstruction(ConstructionsTypes::Type type, vector<Point3D> &points) {
    vector<Hex *> basis(points.size());
    for (int i = 0; i < points.size(); i++) {
        basis[i] = grid[points[i]];
    }
    content.push_back(new Construction(type, basis));
}
const map<Point3D, Hex *> &Map::GetGrid() const {
    return grid;
}

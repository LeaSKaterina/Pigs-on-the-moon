#include "map.h"

using namespace std;

void Map::InitGrid() {
    for (int x = -size + 1; x < size; x++) {
        for (int y = -size + 1; y < size; y++) {
            int z = -x - y;
            if (x + y + z == 0 && abs(z) < size)
                grid[Point3D(x, y, z)] = new Hex(x, y, z);
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
    return this->GetHexByPoint(point)->IsSpecial();
}
void Map::AddConstruction(ConstructionsTypes::Type type, vector<Point3D> &points) {
    vector<Hex *> basis(points.size());
    for (int i = 0; i < points.size(); i++) {
        basis[i] = grid[points[i]];
    }
    content.push_back(new Construction(type, basis));
}
ConstructionsTypes::Type Map::GetType(const Hex &hex) const {
    if(hex.IsSpecial() == false) return ConstructionsTypes::EMPTY;
    return this->content[hex.GetOwnerId()]->GetType();
}

struct QueueElement {
    int pathLength;
    Hex *hex;// path (start, hex)
    QueueElement(int pathLength, Hex *hex) : pathLength(pathLength), hex(hex) {}
};

std::vector<Hex *> Map::GetShortestWay(Hex &startHex, Hex &endHex, const std::vector<Hex *> &blockHexes) {
    std::unordered_map<Point3D, Hex *> visitedHexes;// first unique key (hex), second - previous hex on path
    for (const auto &blockHex : blockHexes) {
        visitedHexes[blockHex->GetCoordinates()] = nullptr;
    }
    std::queue<QueueElement> queue;
    queue.emplace(0, &startHex);

    // walk to endHex
    while (!queue.empty() && visitedHexes.count(endHex.GetCoordinates()) != 1) {
        QueueElement currentElement = queue.front();
        queue.pop();
        for (const auto &direction : Point3D::GetNeighborDirections()) {
            Point3D neighbor = currentElement.hex->GetCoordinates() + direction;
            //add to queue if not visited and not obstacle
            if (visitedHexes.count(neighbor) == 0 && this->IsHexAreExistForPoint(neighbor)
                && this->GetType(*GetHexByPoint(neighbor)) != ConstructionsTypes::OBSTACLE) {
                visitedHexes[neighbor] = currentElement.hex;
                queue.emplace(currentElement.pathLength + 1, GetHexByPoint(neighbor));
            }
        }
    }
    std::vector<Hex *> path;
    if (visitedHexes.count(endHex.GetCoordinates()) == 1){
        Hex *currentHex = &endHex;
        path.push_back(currentHex);
        while(currentHex != &startHex){
            currentHex = visitedHexes[currentHex->GetCoordinates()];
            path.push_back(currentHex);
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

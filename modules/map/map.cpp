#include "map.h"

using namespace std;

Map::Map(int size)  : size(size) {
    InitGrid();
    content.resize(ConstructionsTypes::typesNum);
}

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
    for (auto &[k, h] : grid) {
        delete h;
    }

    for (auto c : content)
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
    content[type] = new Construction(type, basis);
}
ConstructionsTypes::Type Map::GetType(const Hex &hex) {
    if (!hex.IsSpecial()) return ConstructionsTypes::EMPTY;
    return ConstructionsTypes::Type(hex.GetOwnerId());
}

std::vector<Hex *> Map::GetShortestWay(Hex &startHex, Hex &endHex, const std::vector<Hex *> &blockHexes) const {
    std::unordered_map<Point3D, Hex *> visitedHexes;// first unique key (hex), second - previous hex on path
    for (const auto &blockHex : blockHexes) {
        visitedHexes[blockHex->GetCoordinates()] = nullptr;
    }
    std::stack<Hex *> zeroPathChange;
    std::stack<Hex *> onePathChange;
    std::stack<Hex *> twoPathChange;

    zeroPathChange.push(&startHex);
    // walk to endHex
    while (!zeroPathChange.empty() && visitedHexes.count(endHex.GetCoordinates()) != 1) {
        Hex *currentElement = zeroPathChange.top();
        zeroPathChange.pop();
        for (const auto &direction : Point3D::GetNeighborDirections()) {
            Point3D neighbor = currentElement->GetCoordinates() + direction;
            //add to queue if not visited and not obstacle
            if (visitedHexes.count(neighbor) == 0 && this->IsHexAreExistForPoint(neighbor)
                && this->GetType(*GetHexByPoint(neighbor)) != ConstructionsTypes::OBSTACLE) {
                visitedHexes[neighbor] = currentElement;
                Hex *nextHex = GetHexByPoint(neighbor);

                //calc weight modification
                //1 - path traveled, others - heuristic function
                int distChange = 1 + nextHex->GetCoordinates().Distance(endHex.GetCoordinates())
                        - currentElement->GetCoordinates().Distance(endHex.GetCoordinates());

                std::stack<Hex *> *targetStack = &zeroPathChange;
                switch (distChange) {
                    case 1:
                        targetStack = &onePathChange;
                        break;
                    case 2:
                        targetStack = &twoPathChange;
                }
                targetStack->emplace(nextHex);
            }
        }

        //check zero stack
        while(zeroPathChange.empty() && (!onePathChange.empty() || !twoPathChange.empty())){
            zeroPathChange = std::move(onePathChange);
            onePathChange = std::move(twoPathChange);
        }
    }
    std::vector<Hex *> path;
    if (visitedHexes.count(endHex.GetCoordinates()) == 1) {
        Hex *currentHex = &endHex;
        path.push_back(currentHex);
        while (currentHex != &startHex) {
            currentHex = visitedHexes[currentHex->GetCoordinates()];
            path.push_back(currentHex);
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

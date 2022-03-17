#include "map.h"

using namespace std;


void Map::InitGrid() {
    for (int x = -size + 1; x < size; x++) {
        for (int y = -size + 1; y < size; y++) {
            int z = -x - y;
            if (x + y + z == 0 && abs(z) < size)
                grid[Point3D(x, y, z)] = make_unique<Hex>(x, y, z);
        }
    }
}

bool Map::IsBasePoint(const Point3D &point) const {
    return GetHexByPoint(point)->GetType() == ConstructionsTypes::BASE;
}

void Map::AddConstruction(ConstructionsTypes::Type type, vector<Point3D> &points) {
    for (auto &point : points) {
        auto &hex = grid[point];
        hex->SetOwnerId(type);
    }
    if (type == ConstructionsTypes::BASE) {
        pointsOfBase = points;
    }
}

std::vector<Hex *> Map::GetShortestWay(Hex &startHex, Hex &endHex, const std::vector<Hex *> &blockHexes) const {
    std::unordered_map<Point3D, Hex *> visitedHexes;// first unique key (hex), second - previous hex on path
    for (const auto &blockHex : blockHexes) {
        visitedHexes[blockHex->GetCoordinates()] = &startHex;
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
            if (visitedHexes.count(neighbor) == 0 && this->IsHexAreExistForPoint(neighbor) && GetHexByPoint(neighbor)->GetType() != ConstructionsTypes::OBSTACLE) {
                visitedHexes[neighbor] = currentElement;
                Hex *nextHex = GetHexByPoint(neighbor);

                //calc weight modification
                //1 - path traveled, others - heuristic function
                int distChange = 1 + nextHex->GetCoordinates().Distance(endHex.GetCoordinates()) - currentElement->GetCoordinates().Distance(endHex.GetCoordinates());

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
        while (zeroPathChange.empty() && (!onePathChange.empty() || !twoPathChange.empty())) {
            zeroPathChange = std::move(onePathChange);
            onePathChange = std::move(twoPathChange);
        }
    }
    std::vector<Hex *> path;
    if (visitedHexes.count(endHex.GetCoordinates()) == 1 && visitedHexes[endHex.GetCoordinates()] != nullptr) {
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

bool Map::HasObstacleBetween(const Hex &f, const Hex &s) const {

    // Find diagonal :
    int axis;
    int count = 0;
    Point3D checker;

    for (int i = 0; i < 3; i++) {
        if (f.GetCoordinates()[i] != s.GetCoordinates()[i]) {
            axis = i;
            count++;
        } else {
            checker[i] = f.GetCoordinates()[i];
        }
    }

    if (count != 1) return false;

    pair<int, int> borders;
    borders = f < s
                      ? make_pair(f.GetCoordinates()[axis], s.GetCoordinates()[axis])
                      : make_pair(s.GetCoordinates()[axis], s.GetCoordinates()[axis]);

    for (checker[axis] = borders.first + 1; checker[axis] < borders.second; checker[axis]++) {
        if (GetHexByPoint(checker)->GetType() == ConstructionsTypes::Type::OBSTACLE)
            return true;
    }

    return false;
}

vector<Hex *> Map::GetFreePointsOfBase() const {
    vector<Hex *> res;
    for (auto point : pointsOfBase) {
        if (GetHexByPoint(point)->IsEmpty())
            res.push_back(GetHexByPoint(point));
    }
    return res;
}

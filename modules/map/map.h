#pragma once

#include "constructions/construction.h"
#include "enums/types.h"
#include "hex.h"
#include <map>
#include <stack>
#include <unordered_map>

class Map {
public:
    explicit Map(int size);

    void AddConstruction(ConstructionsTypes::Type type, std::vector<Point3D> &points);

    [[nodiscard]] bool IsHexAreExistForPoint(const Point3D &point) const { return grid.count(point) != 0; }

    [[nodiscard]] Hex *GetHexByPoint(const Point3D &p) const { return grid.at(p); }

    [[nodiscard]] bool IsBasePoint(const Hex *point) const;

    [[nodiscard]] bool IsBasePoint(const Point3D &point) const;

    [[nodiscard]] static ConstructionsTypes::Type GetType(const Hex &hex);

    [[nodiscard]] bool HasObstacleBetween(const Hex &f, const Hex &s) const;

    ~Map();

    [[nodiscard]] const std::map<Point3D, Hex *> &GetGrid() const { return grid; }

    [[nodiscard]] const std::vector<Construction *> &GetContent() const { return content; }


    //function return shortest way between two hexes considering specific map and blockHexes as variable.
    //blockHexes is a vector of hexes which we can't visit right now but can visit in general. For example we can add to this vector vehicles point because
    //on the last run this function, we tried to go to the cell occupied by the tank. We can't stand on an occupied cell, but we can drive through it.
    //Algo:
    //Algo is A*. We don't use priority queue. Instead of this we use 3 stacks. First zero length modification (+1 distance traveled -1 path to target),
    //then (+1 traveled +0 path to target), and (+1 traveled +1 to target). Enough considering first stack and if it is empty use next stack.
    //Heuristic function is the shortest path without obstacles.
    std::vector<Hex *> GetShortestWay(Hex &startHex, Hex &endHex, const std::vector<Hex *> &blockHexes = {}) const;

private:
    int size;
    std::vector<Construction *> content;
    std::map<Point3D, Hex *> grid;

    void InitGrid();
};

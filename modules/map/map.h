#pragma once

#include "../constructions/base.h"
#include "../constructions/construction.h"
#include "hex.h"
#include <map>
#include <tuple>
#include <vector>

using namespace std;

class Map {
private:
    int size;
    vector<Construction *> content;
    map<tuple<int, int, int>, Hex *> grid;

    void InitGrid();

public:
    explicit Map(int size) : size(size) { InitGrid(); }

    void AddBase(vector<tuple<int, int, int>> &points);

    [[nodiscard]] Hex *Get(const tuple<int, int, int> &p) const { return grid.at(p); }
};

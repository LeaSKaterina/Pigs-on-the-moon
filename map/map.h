#ifndef PIGS_ON_THE_MOON_MAP_H
#define PIGS_ON_THE_MOON_MAP_H

#pragma once

#include <vector>
#include <tuple>
#include "hex.h"
#include "..\constructions\construction.h"

using namespace std;

class Map {
private:
    int size;
    vector<Construction *> content;
    map<tuple < int, int, int>, Hex*>
    grid;

    void InitGrid();

public:
    Map(int size);

    void AddBase(vector <tuple<int, int, int>> &points);

    Hex *Get(const tuple<int, int, int> &p) const;
};


#endif //PIGS_ON_THE_MOON_MAP_H

#pragma once
#include <string>
#include <tuple>
#include "hex.hpp"
#include "..\constructions\construction.hpp"
#include "..\constructions\base.hpp"
#include <vector>
#include <map>
#include <tuple>
using namespace std;

class Map {
public:
    Map(int size) {
        this->size = size;
        init_grid();
    }

    void add_base(vector<tuple<int, int, int>>& points) {
        vector<Hex*> basis;
        for(auto& p : points) {
            basis.push_back(grid[p]);
        }
        content.push_back(new Base(basis));
    }

    Hex* get(const tuple<int, int, int>& p) const {
        return grid.at(p);
    }

private:
    int size;
    vector<Construction*> content;
    map<tuple<int, int, int>, Hex*> grid; 

    void init_grid() {
        for(int x = -size + 1; x < size; x++) {
            for(int y = -size + 1; y < size; y++) {
                for(int z = 1 - size; z < size; z++) {
                    if (x + y + z == 0)
                        grid[make_tuple(x, y, z)] = new Hex(x, y, z);
                }
            }
        }
    }

};
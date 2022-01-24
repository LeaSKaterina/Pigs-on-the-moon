#pragma once
#include <vector>
#include "..\map\hex.hpp"
#include "..\actors\vehicle.hpp"

class Construction {
public:
    virtual void play(Vehicle* ) {}
    explicit Construction(std::vector<Hex*>& basis) {
        id = counter;
        counter++;

        for (auto& h : basis) {
            h->set_owner_id(id);
        }
    }
private:
    // std::vector<Hex*> basis;
    static int counter;
    int id;
};

int Construction::counter = 0;
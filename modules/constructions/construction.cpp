#include "construction.h"

Construction::Construction(std::vector<Hex *> &basis) {
    id = Construction::counter++;
    for (auto &h : basis) {
        h->SetOwnerId(id);
    }
}

int Construction::counter = 0;

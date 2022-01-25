//
// Created by HP on 25.01.2022.
//

#include "construction.h"

//#pragma once

Construction::Construction(std::vector<Hex*>& basis) {
    id = counter;
    counter++;
    for (auto& h : basis) {
        h->set_owner_id(id);
    }
}

int Construction::counter = 0;
#include "construction.h"

int Construction::counter = 0;

Construction::Construction(ConstructionsTypes::Type type, std::vector<Hex *> &basis) {
    id = Construction::counter++;
    for (auto &h: basis) {
        h->SetOwnerId(id);
    }
    this->type = type;
}

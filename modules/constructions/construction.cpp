#include "construction.h"

Construction::Construction(ConstructionsTypes::Type type, std::vector<Hex *> &basis) {
    for (auto &h : basis) {
        h->SetOwnerId(type);
    }
    this->type = type;
}

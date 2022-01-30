#include "move_controller.h"

#include <cstdlib>
#include "iostream"

void MoveController::ReduceModuleBy(int &n, int amount){
    for (int i = 0; i < amount; i++){
        ModuleDecrement(n);
    }
}

void MoveController::ModuleDecrement(int &n){
    if (n == 0) return;
    if (n>0) n--;
        else n ++;
//    n-- ? n>0 : n++;
}

Hex* MoveController::getNextHex(Hex& hex, Map& map){
    auto[x, y, z] = hex.GetCoordinates();

    if (x == 0 || y == 0 || z == 0){
        if (x == 0){
            ReduceModuleBy(y,2);
            ReduceModuleBy(z,2);
        }
        if (y == 0){
            ReduceModuleBy(x,2);
            ReduceModuleBy(z,2);
        }
        if (z == 0){
            ReduceModuleBy(x,2);
            ReduceModuleBy(y,2);
        }
    } else {

//    придумать, что делать (возвращать), если центр или ячейка занята
//    if (*maxAbs == 0) return map.Get(std::make_tuple(0, 0, 0));
        auto *maxAbs = &x;
        if (abs(*maxAbs) < abs(y)) maxAbs = &y;
        if (abs(*maxAbs) < abs(z)) maxAbs = &z;

        ModuleDecrement(x);
        ModuleDecrement(y);
        ModuleDecrement(z);
        ModuleDecrement(*maxAbs);

        //    std::cout<< maxAbs << " " << *maxAbs << endl;

    }

    std::cout<< x << " " << y << " " <<  z << " " << endl;
    std::cout<< &x << " " << &y << " " <<  &z << " " << endl;

    return map.Get(std::make_tuple(x, y, z));

}

/*
int Hex::GetDistance(Hex &f, Hex &s) {

    auto&[x2, y2, z2] = s.coordinates;
    return (abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)) / 2;
}
*/

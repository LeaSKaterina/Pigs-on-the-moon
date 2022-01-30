#include "action_controller.h"

#include <cstdlib>
#include "iostream"

void ActionController::ReduceModule(int &n, const int amount){
    for (int i = 0; i < amount; i++){
        ModuleDecrement(n);
    }
}

void ActionController::ModuleDecrement(int &n){
    if (n == 0) return;
    if (n>0) n--;
    else n ++;
}

void ActionController::ModuleIncrement(int &n){
//    if (n == 0) return;
    if (n>=0) n++;
    else n--;
}

std::tuple<int,int,int> ActionController::getNextOnAxis(std::tuple<int,int,int> coordinates, Map* map) {
    auto[x, y, z] = coordinates;

    if (x == 0){
        ReduceModule(y, 2);
        ReduceModule(z, 2);
    }
    if (y == 0){
        ReduceModule(x, 2);
        ReduceModule(z, 2);
    }
    if (z == 0){
        ReduceModule(x, 2);
        ReduceModule(y, 2);
    }

    tuple<int,int,int> res = make_tuple(x,y,z);

    if (map->Get(res)->IsEmpty()) return res;

    if (x == 0){
        ModuleIncrement(y);
        x = 0 - y - z;
    }
    if (y == 0){
        ModuleIncrement(z);
        y = 0 - x - z;
    }
    if (z == 0){
        ModuleIncrement(x);
        z = 0 - x - y;
    }

    if (map->Get(res)->IsEmpty()) return res;

    // не работает, ибо (x,y,z) изменены
//    if (x == 0){
//        ModuleIncrement(z);
//        x = 0 - y - z;
//    }
//    if (y == 0){
//        ModuleIncrement(x);
//        y = 0 - x - z;
//    }
//    if (z == 0){
//        ModuleIncrement(y);
//        z = 0 - x - y;
//    }
//
//    if (map->Get(res)->IsEmpty()) return res;
    return std::make_tuple(-1,-1,-1); // нам не нужно перемещаться

}

std::tuple<int,int,int> ActionController::getTargetForMove(std::tuple<int,int,int> coordinates, Map* map){
    auto[x, y, z] = coordinates;
    if (x == 0 || y == 0 || z == 0)
        return getNextOnAxis(coordinates, map);

    auto *maxAbs = &x;
    if (abs(*maxAbs) < abs(y)) maxAbs = &y;
    if (abs(*maxAbs) < abs(z)) maxAbs = &z;

    if (*maxAbs == 0 || abs(*maxAbs) == 1)
        return std::make_tuple(-1,-1,-1); // нам не нужно перемещаться, мы на базе

    ModuleDecrement(x);
    ModuleDecrement(y);
    ModuleDecrement(z);
    ModuleDecrement(*maxAbs);

    tuple<int,int,int> res = make_tuple(x,y,z);
//    std::cout<< x << " " << y << " " <<  z << " " << endl;
//    std::cout<< &x << " " << &y << " " <<  &z << " " << endl;

    if (map->Get(res)->IsEmpty()) return res;


    //если res получился на оси - отдельное поведение (оси зло)

    if (maxAbs == &x){
        ModuleIncrement(y);
        ModuleDecrement(z);
    }
    if (maxAbs == &y){
        ModuleIncrement(x);
        ModuleDecrement(z);
    }
    if (maxAbs == &z){
        ModuleIncrement(x);
        ModuleDecrement(y);
    }

    res = make_tuple(x,y,z);
    if (map->Get(res)->IsEmpty()) return res;


//    return res;
    return std::make_tuple(-1,-1,-1); // нам не нужно перемещаться
}

std::tuple<int, int, int>
ActionController::getTargetForShoot(std::tuple<int, int, int> coordinates, vector<vector<int>> attackMatrix,
                                    vector<vector<Vehicle *>> vehicles, int playerId) {
    return std::tuple<int, int, int>(-1,-1,-1);
} // какая-то логика выстрела. если не стрелять - возвращает (-1,-1,-1)

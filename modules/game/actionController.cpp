#include "actionController.h"

void ActionController::ReduceModule(int &n, const int amount){
    for (int i = 0; i < amount; i++){
        ModuleDecrement(n);
    }
}

void ActionController::IncreaseModule(int &n, const int amount){
    for (int i = 0; i < amount; i++){
        ModuleIncrement(n);
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

void restore(int& x, int& y, int& z, const std::tuple<int,int,int> coordinates){
    x = get<0>(coordinates);
    y = get<1>(coordinates);
    z = get<2>(coordinates);
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

    restore(x,y,z,coordinates);
    if (x == 0){
        ReduceModule(y,2);
        ModuleIncrement(z);
        x = 0 - y - z;
    }
    if (y == 0){
        ReduceModule(z,2);
        ModuleIncrement(x);
        y = 0 - x - z;
    }
    if (z == 0){
        ReduceModule(x,2);
        ModuleIncrement(y);
        z = 0 - x - y;
    }
    res = make_tuple(x,y,z);
    if (map->Get(res)->IsEmpty()) return res;

    restore(x,y,z,coordinates);
    if (x == 0){
        ReduceModule(z,2);
        ModuleIncrement(y);
        x = 0 - y - z;
    }
    if (y == 0){
        ReduceModule(x,2);
        ModuleIncrement(z);
        y = 0 - x - z;
    }
    if (z == 0){
        ReduceModule(y,2);
        ModuleIncrement(x);
        z = 0 - x - y;
    }
    res = make_tuple(x,y,z);
    if (map->Get(res)->IsEmpty()) return res;


    return std::make_tuple(-1,-1,-1); // нам не нужно перемещаться

}

std::tuple<int,int,int> ActionController::getTargetForMove(std::tuple<int,int,int> coordinates, Map* map){
    auto [x, y, z] = coordinates;

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
    if (map->Get(res)->IsEmpty()) return res;


    restore(x,y,z,coordinates);


    if (maxAbs == &x){
        ReduceModule(x,2);
        y = 0 - x - z;
    }
    if (maxAbs == &y){
        ReduceModule(y,2);
        z = 0 - x - y;
    }
    if (maxAbs == &z){
        ReduceModule(z,2);
        x = 0 - y - z;
    }

    res = make_tuple(x,y,z);

    if (map->Get(res)->IsEmpty()) return res;

    restore(x,y,z,coordinates);


    if (maxAbs == &x){
        ReduceModule(x,2);
        z = 0 - x - y;
    }
    if (maxAbs == &y){
        ReduceModule(y,2);
        x = 0 - y - z;
    }
    if (maxAbs == &z){
        ReduceModule(z,2);
        y = 0 - x - z;
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

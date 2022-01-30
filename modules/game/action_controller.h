//#include <tuple>
#include "../map/hex.h"
#include "../map/map.h"

class MoveController {
private:
    static void ModuleDecrement(int &n);
    static void ReduceModuleBy(int &n, int amount);

public:
    static Hex* getNextHex(Hex& hex, Map& map);
};

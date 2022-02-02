#ifndef PIGS_ON_THE_MOON_VEHICLE_TYPES_H
#define PIGS_ON_THE_MOON_VEHICLE_TYPES_H
#include <string>
namespace VehiclesTypes {
    enum Type {
        AtSpg, LightTank, HeavyTank, MediumTank, Spg
    };
    extern int TypesNum;
    extern std::string s_types[];
}
#endif //PIGS_ON_THE_MOON_VEHICLE_TYPES_H

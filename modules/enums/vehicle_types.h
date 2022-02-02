#ifndef PIGS_ON_THE_MOON_VEHICLE_TYPES_H
#define PIGS_ON_THE_MOON_VEHICLE_TYPES_H
#include <string>
namespace VehiclesTypes {
    enum Type {
        AtSpg, LightTank, HeavyTank, MediumTank, Spg
    };
    extern const int TypesNum;
    extern const std::string s_types[];
}
#endif //PIGS_ON_THE_MOON_VEHICLE_TYPES_H

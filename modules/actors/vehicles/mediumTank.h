#ifndef PIGS_ON_THE_MOON_MEDIUMTANK_H
#define PIGS_ON_THE_MOON_MEDIUMTANK_H

#include "vehicle.h"

class MediumTank : public Vehicle {
public:
    MediumTank(int playerId) : Vehicle(playerId, 2, 2) {};

    [[nodiscard]]  std::multimap<int, Point> GetAvailableMovePoints(Point target, int r) const override;

    std::vector<bool> IsAvailableForShoot(const std::vector<Point>& points) override;

    Action PriorityAction() const override {return Action::MOVE;}
};


#endif//PIGS_ON_THE_MOON_MEDIUMTANK_H

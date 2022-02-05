#ifndef PIGS_ON_THE_MOON_LIGHTTANK_H
#define PIGS_ON_THE_MOON_LIGHTTANK_H

#include "vehicle.h"

class LightTank : public Vehicle {

public:
    explicit LightTank(int playerId) : Vehicle(playerId, 1, 3){};

    [[nodiscard]] std::multimap<int, Point> GetAvailableMovePoints(Point target, int r) const override;

    std::vector<bool> IsAvailableForShoot(const std::vector<Point>& points) override;

    Action PriorityAction() const override {return Action::SHOOT;}
};


#endif//PIGS_ON_THE_MOON_LIGHTTANK_H

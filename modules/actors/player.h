#pragma once

#include <string>
#include <utility>

struct Player {
private:
    const std::string NAME;
    const std::string PASSWORD;
    int id;

public:
    Player(int id, std::string name, std::string pass) : id(id),
                                                         NAME(std::move(name)),
                                                         PASSWORD(std::move(pass)) {}

    [[nodiscard]] int GetId() const { return id; }
};

#pragma once

#include <string>
#include <utility>

struct Player {
private:
    const std::string name;
    const std::string password;
    int id;

public:
    Player(int id, std::string name, std::string pass) : id(id),
                                                         name(std::move(name)),
                                                         password(std::move(pass)) {}
    [[nodiscard]] int GetId() const { return id; }
};

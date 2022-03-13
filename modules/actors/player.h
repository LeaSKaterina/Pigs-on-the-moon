#pragma once

#include <string>
#include <utility>

struct Player {
public:
    Player(int id, std::string name, std::string pass, bool isObserver = false) : id(id),
                                                                                  name(std::move(name)),
                                                                                  password(std::move(pass)),
                                                                                  isObserver(isObserver) {}

    [[nodiscard]] int GetId() const { return id; }


    [[nodiscard]] bool IsObserver() const { return isObserver; }

private:
    const std::string name;
    const std::string password;
    int id;
    bool isObserver;
};

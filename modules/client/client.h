#ifndef PIGS_ON_THE_MOON_CLIENT_CLIENT_H
#define PIGS_ON_THE_MOON_CLIENT_CLIENT_H

#include <winsock2.h>
#include <winerror.h>
#include <iostream>
#include <memory>
#include <valarray>
#include "../enums/action.h"
#include "../enums/result.h"

#include "../../libs/json-3.10.5/include/nlohmann/json.hpp"


struct Response{
    Result result;
    nlohmann::json answer;

    friend std::ostream& operator<< (std::ostream &out, const Response &response);
};

class Client {
private:
    const char ADDRESS[14] = {"92.223.34.102"};
    const int PORT = 443;
    SOCKET server; // server descriptor
    const int PROTOCOL = AF_INET; //socket config
    const int SOCKET_TYPE = SOCK_STREAM; // socket config
    WSAData WSAData; //info about connect

    void SendRequest(Action action, const std::string& msg) const;
    int GetIntFromServer() const;
    Response GetAnswer() const;

    bool debug;
public:
    Client(bool debug = true);
    ~Client();

    Response Login(const std::string& name, const std::string& password = "",
                   const std::string& game="", int num_turns = 0, int num_players = 1, bool is_observer = false) const;
    Response Logout() const;
    Response Map() const;
    Response GameState() const;
    Response GameActions() const;
    Response Turn() const;
    Response Chat(const std::string& msg) const;
    Response Move(int vehicle_id, int x, int y, int z) const;
    Response Shoot(int vehicle_id, int x, int y, int z) const;

    static void PrintLogInfo(const std::string& info);
};


#endif //PIGS_ON_THE_MOON_CLIENT_CLIENT_H
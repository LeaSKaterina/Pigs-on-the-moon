#include "Client.h"

Client::Client() {
    if(FAILED (WSAStartup(MAKEWORD(2, 1), &this->WSAData))){// first - version, second create info
        PrintLogInfo("WSAStartup creation failed with error: " + std::to_string(WSAGetLastError()));
    }
    if ((this->server = socket(this->PROTOCOL, this->SOCKET_TYPE, 0)) == INVALID_SOCKET) {
        PrintLogInfo("Socket creation failed with error: " + std::to_string(WSAGetLastError()));
    }
    sockaddr_in myaddr;

    myaddr.sin_addr.s_addr = inet_addr(this->ADDRESS);
    myaddr.sin_family = this->PROTOCOL;
    myaddr.sin_port = htons(this->PORT);

    if (connect(this->server, (SOCKADDR* ) &myaddr, sizeof(myaddr)) == SOCKET_ERROR) {
        PrintLogInfo("Server connection failed with error: " + std::to_string(WSAGetLastError()));
    }
}

Client::~Client() {
    shutdown(server, 1);
}

void Client::PrintLogInfo(const std::string& info) {
    std::cout << info << '\n';
}

void Client::SendRequest(Action action, const std::string& msg) const {
    std::unique_ptr<char[]> buffer(new char[4 * 2 + msg.size()]);

    {
        auto actionInt = (unsigned int) action;
        unsigned int size = msg.size();
        for (int i = 0; i < 4; ++i) {
            buffer[i] = char(actionInt % 256);
            buffer[i + 4] = char(size % 256);
            actionInt >>= 8;
            size >>= 8;
        }
    }

    unsigned int sizeMsg = msg.size();

    for (int i = 0; i < sizeMsg; i++) {
        buffer[i + 8] = msg[i];
    }
//    for (int i = 0; i < 8; ++i) {           //Debug code
//        std::cout << int(buffer[i]) << ' ';
//    }
//    for (int i = 8; i < 8 + sizeMsg; ++i) {
//        std::cout << buffer[i];
//    }
//    std::cout << '\n';                     //End debug code
    send(server, buffer.get(), 8 + sizeMsg, 0);
}

Response Client::GetAnswer() const {
    auto result = Result(GetIntFromServer());
    unsigned int size = GetIntFromServer();

    std::unique_ptr<char[]> cMsg(new char[size + 1]);
    cMsg[size] = '\0';
    if (size != 0) recv(server, cMsg.get(), size, 0);
    nlohmann::json ans (cMsg.get());

    return {result, ans};
}

int Client::GetIntFromServer() const {
    char buffer[4];
    recv(server, buffer, 4, 0);

    int result = 0;
    for (int i = 0; i < 4; ++i) {
        result += (unsigned char)buffer[i] * std::pow(2, i * 8);
    }
    return result;
}

Response Client::Login(const std::string& name, const std::string& password, const std::string& game, int num_turns, int num_players, bool is_observer) const{
    nlohmann::json json;
    json["name"] = name;
    json["password"] = password;
    json["game"] = game;
    json["num_turns"] = num_turns;
    json["num_players"] = num_players;
    json["is_observer"] = is_observer;

    this->SendRequest(Action::LOGIN, json.dump());

    return this->GetAnswer();
}

Response Client::Logout() const {
    this->SendRequest(Action::LOGOUT, "");
    return this->GetAnswer();
}

Response Client::Map() const{
    this->SendRequest(Action::MAP, "");
    return this->GetAnswer();
}

Response Client::GameState() const {
    this->SendRequest(Action::GAME_STATE, "");
    return this->GetAnswer();
}

Response Client::GameActions() const {
    this->SendRequest(Action::GAME_ACTIONS, "");
    return this->GetAnswer();
}

Response Client::Turn() const {
    this->SendRequest(Action::TURN, "");
    return this->GetAnswer();
}

Response Client::Chat(const std::string& msg) const {
    this->SendRequest(Action::CHAT, msg);
    return this->GetAnswer();
}

Response Client::Move(int vehicle_id, int x, int y, int z) const {
    nlohmann::json msg;
    msg["vehicle_id"] = vehicle_id;
    msg["target"]["x"] = x;
    msg["target"]["y"] = y;
    msg["target"]["z"] = z;

    this->SendRequest(Action::MOVE, msg.dump());
    return this->GetAnswer();
}

Response Client::Shoot(int vehicle_id, int x, int y, int z) const {
    nlohmann::json msg;
    msg["vehicle_id"] = vehicle_id;
    msg["target"]["x"] = x;
    msg["target"]["y"] = y;
    msg["target"]["z"] = z;
    this->SendRequest(Action::SHOOT, msg);
    return this->GetAnswer();
}

Response Client::Move(const std::string& msg) const {
    this->SendRequest(Action::MOVE, msg);
    return this->GetAnswer();
}

Response Client::Shoot(const std::string &msg) const {
    this->SendRequest(Action::SHOOT, msg);
    return this->GetAnswer();
}

std::ostream &operator<<(std::ostream &out, const Response &response) {
    out << "Response {result : " << response.result << ", answer : " << response.answer << " }";
    return out;
}

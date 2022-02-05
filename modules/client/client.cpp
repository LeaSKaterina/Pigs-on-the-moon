#include "client.h"

Client::Client() {
    if (FAILED(WSAStartup(MAKEWORD(2, 1), &this->WSAData))) {// first - version, second create info
        PrintLogInfo("WSAStartup creation failed with error: " + std::to_string(WSAGetLastError()));
    }
    if ((this->server = socket(this->PROTOCOL, this->SOCKET_TYPE, 0)) == INVALID_SOCKET) {
        PrintLogInfo("Socket creation failed with error: " + std::to_string(WSAGetLastError()));
    }
    sockaddr_in myaddr;

    myaddr.sin_addr.s_addr = inet_addr(this->ADDRESS);
    myaddr.sin_family = this->PROTOCOL;
    myaddr.sin_port = htons(this->PORT);

    if (connect(this->server, (SOCKADDR *) &myaddr, sizeof(myaddr)) == SOCKET_ERROR) {
        PrintLogInfo("Server connection failed with error: " + std::to_string(WSAGetLastError()));
    }
}

void Client::SendRequest(Action action, const std::string &msg) const {
    std::vector<char> buffer(4 * 2 + msg.size() + 1);// action(int) + size(int) + msg + '\0'
    buffer.back() = '\0';

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

    std::strncpy(&buffer[8], &msg[0], msg.size());
#ifdef _DEBUG
    for (int i = 0; i < 4; ++i) {
        std::cerr << (int) buffer[i] << ' ';
    }
    for (int i = 0; i < 4; ++i) {
        std::cerr << (int) buffer[i + 4] << ' ';
    }
    std::cerr << &buffer[8] << '\n';
#endif

    send(server, &buffer.front(), 8 + msg.size(), 0);
}

Response Client::GetAnswer() const {
    auto result = Result(GetIntFromServer());
    int size = GetIntFromServer();

    std::vector<char> msg(size);
    if (size) recv(server, &msg.front(), size, MSG_WAITALL);
    nlohmann::ordered_json ans = size ? nlohmann::ordered_json::parse(msg)
                                      : nlohmann::ordered_json();
    #ifdef _DEBUG
//        std::cerr << (int)result << " " << ans << std::endl;
    #endif
    return {result, ans};
}

int Client::GetIntFromServer() const {
    char buffer[4];
    recv(server, buffer, 4, 0);

    int result = 0;
    for (int i = 0; i < 4; ++i) {
        result += (unsigned char) buffer[i] * (int) std::pow(2, i * 8);
    }
    return result;
}

Response Client::Login(const std::string &name, const std::string &password, const std::string &game, int numTurns,
                       int numPlayers, bool isObserver) const {
    nlohmann::ordered_json json;
    json["name"] = name;
    json["password"] = password;
    if (!game.empty())
        json["game"] = game;
    if (numTurns != 0)
        json["num_turns"] = numTurns;
    json["num_players"] = numPlayers;
    json["is_observer"] = isObserver;

    this->SendRequest(Action::LOGIN, json.dump());

    return this->GetAnswer();
}

Response Client::Chat(const std::string &msg) const {
    nlohmann::ordered_json json;
    json["message"] = msg;
    this->SendRequest(Action::CHAT, json.dump());
    return this->GetAnswer();
}

Response Client::Move(int vehicleId, int x, int y, int z) const {
    nlohmann::ordered_json msg;
    msg["vehicle_id"] = vehicleId;
    msg["target"]["x"] = x;
    msg["target"]["y"] = y;
    msg["target"]["z"] = z;

    this->SendRequest(Action::MOVE, msg.dump());
    return this->GetAnswer();
}

Response Client::Shoot(int vehicleId, int x, int y, int z) const {
    nlohmann::ordered_json msg;
    msg["vehicle_id"] = vehicleId;
    msg["target"]["x"] = x;
    msg["target"]["y"] = y;
    msg["target"]["z"] = z;
    this->SendRequest(Action::SHOOT, msg);
    return this->GetAnswer();
}

std::ostream &operator<<(std::ostream &out, const Response &response) {
    out << "Response {result : " << (int) response.result << ", answer :\n"
        << response.answer.dump(2) << " }\n";
    return out;
}

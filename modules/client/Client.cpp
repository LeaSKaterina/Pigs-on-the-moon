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
        int action_int = (int) action;
        int size = msg.size();
        for (int i = 0; i < 4; ++i) {
            buffer[i] = char(action_int % 256);
            buffer[i + 4] = char(size % 256);
            action_int >>= 8;
            size >>= 8;
        }
    }

    int size_msg = msg.size();

    for (int i = 0; i < size_msg; i++) {
        buffer[i + 8] = msg[i];
    }
//    for (int i = 0; i < 8; ++i) {
//        std::cout << int(buffer[i]) << ' ';
//    }
//    for (int i = 8; i < 8 + size_msg; ++i) {
//        std::cout << buffer[i];
//    }
//    std::cout << '\n';
    send(server, buffer.get(), 8 + size_msg, 0);
}

Response Client::GetAnswer() const {
    auto result = Result(GetIntFromServer());
    int size = Result(GetIntFromServer());

    std::unique_ptr<char[]> c_msg(new char[size + 1]);
    c_msg[size] = '\0';
    if (size != 0) recv(server, c_msg.get(), size, 0);
    std::string msg(c_msg.get());

    return {result, msg};
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
    std::string msg = "{\"name\":\"" + name +
                      "\",\"password\":\"" + password +
                      "\",\"game\":\"" + game +
                      "\",\"num_turns\":" + std::to_string(num_turns) +
                      ",\"num_players\":" + std::to_string(num_players) +
                      ",\"is_observer\":" + std::to_string(is_observer) + "}";
    this->SendRequest(Action::LOGIN, msg);

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
    std::string str = "{\"vehicle_id\":" + std::to_string(vehicle_id) +
            ",\"target\":{\" + x\":" + std::to_string(x) +
            ",\"y\":" + std::to_string(y) +
            ",\"z\":" + std::to_string(z) +
            "}}";
    this->SendRequest(Action::MOVE, str);
    return this->GetAnswer();
}

Response Client::Shoot(int vehicle_id, int x, int y, int z) const {
    std::string str = "{\"vehicle_id\":" + std::to_string(vehicle_id) +
                      ",\"target\":{\" + x\":" + std::to_string(x) +
                      ",\"y\":" + std::to_string(y) +
                      ",\"z\":" + std::to_string(z) +
                      "}}";
    this->SendRequest(Action::SHOOT, str);
    return this->GetAnswer();
}

std::ostream &operator<<(std::ostream &out, const Response &response) {
    out << "Response {result : " << response.result << ", answer : " << response.answer << " }";
    return out;
}

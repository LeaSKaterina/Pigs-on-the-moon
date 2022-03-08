#include "client.h"

Client::Client() {
    sf::Socket::Status status = tcpSocket.connect(this->address, this->port);
    if (status != sf::Socket::Done) {
        throw std::invalid_argument("can't connect ot server");
    }
    if (status != sf::Socket::Done) {
        PrintLogInfo("can't connect to server" + status);
    }
}

void Client::SendRequest(Action action, const std::string &msg) {
    std::vector<char> buffer(codeSize * 2 + msg.size() + 1);// action(int) + size(int) + msg + '\0'
    buffer.back() = '\0';

    {
        auto actionInt = (unsigned int) action;
        unsigned int size = msg.size();
        for (int i = 0; i < codeSize; ++i) {
            buffer[i] = char(actionInt % 256);
            buffer[i + codeSize] = char(size % 256);
            actionInt >>= 8;
            size >>= 8;
        }
    }

    std::strncpy(&buffer[codeSize * 2], &msg[0], msg.size());
#ifdef _DEBUG
    for (int i = 0; i < codeSize * 2; ++i) {
        std::cerr << (int) buffer[i] << ' ';
    }
    std::cerr << &buffer[codeSize * 2] << '\n';
#endif

    tcpSocket.send(&buffer.front(), codeSize * 2 + msg.size());
}

std::vector<char> Client::Receive(size_t size) {
    std::vector<char> msg(size);
    size_t receiveSize = 0;
    size_t totalReceive = 0;
    while (totalReceive != size) {
        tcpSocket.receive(&msg[totalReceive], size, receiveSize);
        totalReceive += receiveSize;
    }
    return msg;
}

Response Client::GetAnswer() {
    auto result = Result(GetIntFromServer());
    int size = GetIntFromServer();

    std::vector<char> msg = std::move(this->Receive(size));

    nlohmann::ordered_json ans = size ? nlohmann::ordered_json::parse(msg)
                                      : nlohmann::ordered_json();
    return {result, ans};
}

int Client::GetIntFromServer() {
    std::vector<char> buffer = std::move(this->Receive(codeSize));

    int result = 0;
    for (int i = 0; i < codeSize; ++i) {
        result += (unsigned char) buffer[i] * (int) std::pow(2, i * 8);
    }
    return result;
}

Response Client::Login(const std::string &name, const std::string &password, const std::string &game, int numTurns,
                       int numPlayers, bool isObserver) {
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

Response Client::Chat(const std::string &msg) {
    nlohmann::ordered_json json;
    json["message"] = msg;
    this->SendRequest(Action::CHAT, json.dump());
    return this->GetAnswer();
}

Response Client::SendTankAction(Action action, int vehicleId, int x, int y, int z) {
    nlohmann::ordered_json msg;
    msg["vehicle_id"] = vehicleId;
    msg["target"]["x"] = x;
    msg["target"]["y"] = y;
    msg["target"]["z"] = z;
    this->SendRequest(action, msg.dump());
    return this->GetAnswer();
}

std::ostream &operator<<(std::ostream &out, const Response &response) {
    out << "Response {result : " << (int) response.result << ", answer :\n"
        << response.answer.dump(2) << " }\n";
    return out;
}

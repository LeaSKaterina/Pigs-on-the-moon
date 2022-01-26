#include <iostream>
#include "modules/client/Client.h"

int main() {
    Client client;
    std::cout << client.Login("test2") << '\n';
    std::cout << client.Move(250, 1,2,2) << '\n';

//    std::cout << client.Map() << '\n';
    std::cout << client.Logout() << '\n';



    return 0;
}

#pragma once


#include "AI/AIClient.h"
#include "gui/view/View.h"


class Controller {
public:
    // Basic constructor
    Controller(const std::string &gameName, int waitTime, int numberPlayers, bool basic);
    // Console run
    Controller(const std::string &gameName, int waitTime, int numberPlayers);
    // Menu run
    Controller(const std::string &gameName, int waitTime, int numberPlayers,
               std::shared_ptr<sf::RenderWindow> &window, bool mute_music);

    virtual ~Controller();

    bool GetIsWindowClose() {
        sf::Lock lock(closeMutex);
        return isWindowClose;
    };

    void CloseGame() {
        sf::Lock lock(closeMutex);
        isWindowClose = true;
    }

    void Run();


private:
    const int waitTime;
    AIClient observer;
    sf::Thread observerThread;
    std::unique_ptr<View> view;
    sf::Mutex observerMutex;
    bool isWindowClose = false;
    sf::Mutex closeMutex;


    void ObserverThread();
};

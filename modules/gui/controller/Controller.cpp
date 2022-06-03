#include "Controller.h"

#include <utility>

Controller::Controller(const std::string &gameName, int waitTime, int numberPlayers)
    : Controller(gameName, waitTime, numberPlayers, true) {

    view = std::make_unique<View>(*this, observer.GetGame(), observerMutex);

    observerThread.launch();
    view->Show();
}

Controller::Controller(const std::string &gameName, int waitTime, int numberPlayers,
                       std::shared_ptr<sf::RenderWindow> &window, bool mute_music)
    : Controller(gameName, waitTime, numberPlayers, true) {
    view = std::make_unique<View>(*this, observer.GetGame(), observerMutex,
                                  window, mute_music);

    observerThread.launch();
    view->Show();
}

Controller::Controller(const std::string &gameName, int waitTime, int numberPlayers, bool)
    : observer("observer", "", gameName, 0, numberPlayers, true),
      observerThread(&Controller::ObserverThread, this),
      waitTime(waitTime) {}

Controller::~Controller() {
    observerThread.wait();
}

void Controller::ObserverThread() {
    observer.ConnectPlayer();
    while (!observer.GameIsFinished() && !GetIsWindowClose()) {
        sf::Lock lock(observerMutex);
        observer.UpdateGameState();
        observerMutex.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(this->waitTime));
        observer.SendTurn();
    }
}

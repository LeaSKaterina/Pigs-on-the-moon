#include "Controller.h"

#include <utility>

Controller::Controller(std::string gameName, int waitTime, int numberPlayers) :
                                                             observer("Den-obs", "", game, 0, numberPlayers, true),
                                                             observerThread(&Controller::ObserverThread, this),
                                                             view(*this, observer.GetGame(), observerMutex),
                                                             waitTime(waitTime), game(std::move(gameName)) {
    observerThread.launch();

    view.Show();
}

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

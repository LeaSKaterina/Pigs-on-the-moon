#include "Bot.h"
#include "gui/controller/Controller.h"



void Bot::StartAI() {
    gc.InitIds();
    while (!gc.GameIsFinished() && !controller.GetIsWindowClose()) {
        std::cout << "Bot\n";
        gc.UpdateGameState();
        if (gc.IsPlayTime())// play only our turn
//                gc.SendAction();

#ifdef _DEBUG
            std::cerr << "\n---------------------------------------\n";
#endif
        gc.SendTurn();
    }
}

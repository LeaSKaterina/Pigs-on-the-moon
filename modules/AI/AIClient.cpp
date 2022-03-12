#include "AIClient.h"

void AIClient::SendAction() const {
    GameClient::SendAction(ai->Play());
}

#include "ClientControls.h"

void ClientControls::SendFirstPlayer(CommandCode cmd) { client.TrySendRequest(cmd, 0); }
void ClientControls::SendSecondPlayer(CommandCode cmd) {
    if (!hasSecondPlayer)
        return;
    client.TrySendRequest(cmd, 1);
}

ClientControls::ClientControls(Client& client): client(client), hasSecondPlayer(false) {}
ClientControls::~ClientControls() = default;

void ClientControls::SetSecondPlayer(bool secondPlayer) { this->hasSecondPlayer = secondPlayer; }

void ClientControls::TakeInputEvent(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
            int key = keyEvent.keysym.sym;

            if (pressedKeysSet.contains(key))
                return;
            pressedKeysSet.insert(key);

            if (key_down.contains(key))
                key_down[key]();

        } break;
        case SDL_KEYUP: {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
            int key = keyEvent.keysym.sym;

            pressedKeysSet.erase(key);

            if (key_up.contains(key))
                key_up[key]();

            break;
        }
    }
}

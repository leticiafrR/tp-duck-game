#ifndef CLIENT_CONTROLS_H
#define CLIENT_CONTROLS_H

#include <set>
#include <unordered_map>

#include "client/Framework.h"
#include "client/network/Client.h"

using std::set;
using std::unordered_map;

class ClientControls {
private:
    Client& client;
    bool hasSecondPlayer;
    set<int> pressedKeysSet;

    unordered_map<int, Callback> key_down = {
            {SDL_KeyCode::SDLK_a, [this]() { SendFirstPlayer(CommandCode::MoveLeft_KeyDown); }},
            {SDL_KeyCode::SDLK_d, [this]() { SendFirstPlayer(CommandCode::MoveRight_KeyDown); }},
            {SDL_KeyCode::SDLK_w, [this]() { SendFirstPlayer(CommandCode::LookUp_KeyDown); }},
            {SDL_KeyCode::SDLK_s, [this]() { SendFirstPlayer(CommandCode::Crouch_KeyDown); }},
            {SDL_KeyCode::SDLK_SPACE, [this]() { SendFirstPlayer(CommandCode::Jump); }},
            {SDL_KeyCode::SDLK_f, [this]() { SendFirstPlayer(CommandCode::UseItem_KeyDown); }},
            {SDL_KeyCode::SDLK_e, [this]() { SendFirstPlayer(CommandCode::CollectItem); }},
            {SDL_KeyCode::SDLK_g, [this]() { SendFirstPlayer(CommandCode::DropItem); }},
            {SDL_KeyCode::SDLK_c, [this]() { SendFirstPlayer(CommandCode::Cuack); }},

            {SDL_KeyCode::SDLK_LEFT, [this]() { SendSecondPlayer(CommandCode::MoveLeft_KeyDown); }},
            {SDL_KeyCode::SDLK_RIGHT,
             [this]() { SendSecondPlayer(CommandCode::MoveRight_KeyDown); }},
            {SDL_KeyCode::SDLK_UP, [this]() { SendSecondPlayer(CommandCode::LookUp_KeyDown); }},
            {SDL_KeyCode::SDLK_DOWN, [this]() { SendSecondPlayer(CommandCode::Crouch_KeyDown); }},
            {SDL_KeyCode::SDLK_RSHIFT, [this]() { SendSecondPlayer(CommandCode::Jump); }},
            {SDL_KeyCode::SDLK_j, [this]() { SendSecondPlayer(CommandCode::UseItem_KeyDown); }},
            {SDL_KeyCode::SDLK_k, [this]() { SendSecondPlayer(CommandCode::CollectItem); }},
            {SDL_KeyCode::SDLK_l, [this]() { SendSecondPlayer(CommandCode::DropItem); }},
            {SDL_KeyCode::SDLK_o, [this]() { SendSecondPlayer(CommandCode::Cuack); }}};

    unordered_map<int, Callback> key_up = {
            {SDL_KeyCode::SDLK_a, [this]() { SendFirstPlayer(CommandCode::MoveLeft_KeyUp); }},
            {SDL_KeyCode::SDLK_d, [this]() { SendFirstPlayer(CommandCode::MoveRight_KeyUp); }},
            {SDL_KeyCode::SDLK_w, [this]() { SendFirstPlayer(CommandCode::LookUp_KeyUp); }},
            {SDL_KeyCode::SDLK_s, [this]() { SendFirstPlayer(CommandCode::Crouch_KeyUp); }},
            {SDL_KeyCode::SDLK_f, [this]() { SendFirstPlayer(CommandCode::UseItem_KeyUp); }},

            {SDL_KeyCode::SDLK_LEFT, [this]() { SendSecondPlayer(CommandCode::MoveLeft_KeyUp); }},
            {SDL_KeyCode::SDLK_RIGHT, [this]() { SendSecondPlayer(CommandCode::MoveRight_KeyUp); }},
            {SDL_KeyCode::SDLK_UP, [this]() { SendSecondPlayer(CommandCode::LookUp_KeyUp); }},
            {SDL_KeyCode::SDLK_DOWN, [this]() { SendSecondPlayer(CommandCode::Crouch_KeyUp); }},
            {SDL_KeyCode::SDLK_j, [this]() { SendSecondPlayer(CommandCode::UseItem_KeyUp); }}};

    void SendFirstPlayer(CommandCode cmd);
    void SendSecondPlayer(CommandCode cmd);

public:
    explicit ClientControls(Client& client);
    ~ClientControls();

    void SetSecondPlayer(bool secondPlayer);

    void TakeInputEvent(SDL_Event event);
};

#endif

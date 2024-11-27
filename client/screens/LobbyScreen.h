#ifndef LOBBY_SCREEN_H
#define LOBBY_SCREEN_H
#include <memory>

#include "client/network/Client.h"
#include "client/tweening/TweenManager.h"
#include "data/networkMsg.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/audio/AudioManager.h"
#include "multimedia/gui/ButtonsManager.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Text.h"

#include "LoadingScreen.h"

using std::shared_ptr;

class LobbyScreen {
private:
    Camera& cam;
    Client& client;
    bool isOwner;

    bool running = false;
    bool waitingToStart = false;

public:
    LobbyScreen(Camera& cam, Client& client, bool isOwner);

    ~LobbyScreen();

    std::shared_ptr<MatchStartDto> Render();
};

#endif

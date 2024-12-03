#ifndef LOBBY_SCREEN_H
#define LOBBY_SCREEN_H
#include <memory>

#include "client/network/Client.h"
#include "client/tweening/TweenManager.h"
#include "data/networkMsg.h"
#include "multimedia/BaseScreen.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/audio/AudioManager.h"
#include "multimedia/gui/ButtonsManager.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Text.h"

#include "LoadingScreen.h"

using std::shared_ptr;

class LobbyScreen: public BaseScreen {
private:
    Client& client;
    bool isOwner;
    shared_ptr<MatchStartDto>& matchData;
    bool waitingToStart = false;

    Button* startButton;
    Text* startButtonText;
    Text* waitingText;

    void OnStartButtonPressed();

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

public:
    LobbyScreen(Camera& cam, ResourceManager& resource, bool& wasClosed, Client& client,
                bool isOwner, shared_ptr<MatchStartDto>& matchData);

    ~LobbyScreen();
};

#endif

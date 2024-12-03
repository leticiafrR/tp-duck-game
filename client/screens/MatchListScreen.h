#ifndef MATCH_LIST_SCREEN_H
#define MATCH_LIST_SCREEN_H

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "client/network/Client.h"
#include "client/tweening/ImageTween.h"
#include "client/tweening/TweenManager.h"
#include "data/networkMsg.h"
#include "multimedia/BaseScreen.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/ButtonsManager.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Image.h"
#include "multimedia/gui/Text.h"

#include "ControlsScreen.h"
#include "LoadingScreen.h"
#include "LobbyItemWidget.h"
#include "PlayersCountSelection.h"

using std::list;
using std::shared_ptr;
using std::string;
using std::vector;

class MatchListScreen: public BaseScreen {
private:
    Client& client;
    list<LobbyItemWidget> widgets;

    float currentY = 0;
    float scrollSize = 0;

    Button* refreshButton;

    ControlsScreen controls;

    PlayersCountSelection playersCountSelection;

    bool& isOwner;

    void OnCreatePressed();

    void OnJoinLobbyPressed(int id);

    void OnRefreshPressed();

    void WaitRefresh();

    void LoadWidgetList(std::vector<DataMatch> data);

    void UpdateWidgetListPosition(Vector2D movement);

    void InitHeader();
    void InitControlsButton();
    void InitCreateButton();
    void InitRefreshButton();

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

public:
    MatchListScreen(Camera& cam, ResourceManager& resource, bool& wasClosed, Client& cl,
                    bool& isOwner);

    ~MatchListScreen();
};

#endif

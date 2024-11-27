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
#include "multimedia/Button.h"
#include "multimedia/ButtonsManager.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/GUIManager.h"
#include "multimedia/Image.h"
#include "multimedia/Text.h"

#include "ControlsScreen.h"
#include "LoadingScreen.h"
#include "LobbyItemWidget.h"
#include "PlayersCountSelection.h"

using std::list;
using std::shared_ptr;
using std::string;
using std::vector;

class MatchListScreen {
private:
    Camera& cam;
    Client& client;
    list<LobbyItemWidget> widgets;

    float currentY = 0;
    float scrollSize = 0;

    bool running = false;
    bool isOwner = false;

    Image header;
    Text titleText;

    Button createButton;
    Text createButtonText;

    Text joinLobbyText;

    Button refreshButton;
    Text refreshButtonText;

    Button controlsButton;
    Text controlsButtonText;

    ControlsScreen controls;

    PlayersCountSelection playersCountSelection;

    void OnCreatePressed();

    void OnJoinLobbyPressed(int id);

    void OnRefreshPressed();

    void WaitRefresh();

    void LoadWidgetList(std::vector<DataMatch> data);

    void UpdateWidgetListPosition(Vector2D movement);

public:
    MatchListScreen(Camera& c, Client& cl);

    ~MatchListScreen();

    bool Render();
};

#endif

#ifndef LOBBIES_LIST_SCREEN_H
#define LOBBIES_LIST_SCREEN_H

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "client/Framework.h"
#include "client/FrameworkUI.h"
#include "client/network/Client.h"
#include "data/networkMsg.h"

#include "ControlsPanel.h"
#include "LoadingScreen.h"
#include "LobbyItemWidget.h"
#include "PlayersCountSelectionPanel.h"

using std::list;
using std::shared_ptr;
using std::string;
using std::vector;

class LobbiesListScreen: public BaseScreen {
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
    LobbiesListScreen(Camera& cam, ResourceManager& resource, bool& wasClosed, Client& cl,
                      bool& isOwner);

    ~LobbiesListScreen();
};

#endif

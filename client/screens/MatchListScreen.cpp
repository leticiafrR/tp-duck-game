#include "MatchListScreen.h"

void MatchListScreen::OnCreatePressed() {
    gameKit.PlayButtonSFX();
    playersCountSelection.Display([this](uint8_t playersCount) {
        bool createSuccess;
        client.CreateMatch(playersCount);
        LoadingScreen loading(
                gameKit, wasClosed,
                [this, &createSuccess]() {
                    if (!client.IsConnected()) {
                        running = false;
                        return true;
                    }

                    std::shared_ptr<ResultJoining> joinResult = nullptr;
                    if (client.TryRecvNetworkMsg(joinResult)) {
                        createSuccess = joinResult->eCode == 0;
                        return true;
                    }
                    return false;
                },
                "Creating match");

        loading.Run();

        if (wasClosed || !running)
            return;

        if (createSuccess) {
            isOwner = true;
            running = false;
        }
    });
}

void MatchListScreen::OnJoinLobbyPressed(int id) {
    gameKit.PlayButtonSFX();

    playersCountSelection.Display([this, id](uint8_t playersCount) {
        bool joinSuccess;
        client.SelectMatch(id, playersCount);
        LoadingScreen loading(
                gameKit, wasClosed,
                [this, &joinSuccess]() {
                    std::shared_ptr<ResultJoining> joinResult = nullptr;
                    if (client.TryRecvNetworkMsg(joinResult)) {
                        joinSuccess = joinResult->eCode == 0;
                        return true;
                    }
                    return false;
                },
                "Joining match");
        loading.Run();
        if (wasClosed || !running)
            return;

        if (joinSuccess) {
            isOwner = false;
            running = false;
        }
    });
}

void MatchListScreen::OnRefreshPressed() {
    gameKit.PlayButtonSFX();
    refreshButton.SetInteractable(false);
    client.Refresh();
    WaitRefresh();
    refreshButton.SetInteractable(true);
}

void MatchListScreen::WaitRefresh() {
    LoadingScreen loading(
            gameKit, wasClosed,
            [this]() {
                std::shared_ptr<AvailableMatches> lobbyListResult = nullptr;
                if (client.TryRecvNetworkMsg(lobbyListResult)) {
                    LoadWidgetList(lobbyListResult->matches);
                    return true;
                }
                return false;
            },
            "Getting available lobbies");
    loading.Run();
}

void MatchListScreen::LoadWidgetList(std::vector<DataMatch> data) {
    widgets.clear();

    Vector2D initialPos(0, -400);
    int moveDelta = 130;

    for (size_t i = 0; i < data.size(); i++) {
        auto lobbyData = data[i];
        widgets.emplace_back(lobbyData.matchID, lobbyData.creatorNickname, lobbyData.currentPlayers,
                             lobbyData.maxPlayers,
                             [this](int id) { this->OnJoinLobbyPressed(id); });

        widgets.back().MoveContent(Vector2D::Down() * i * moveDelta + initialPos);
    }

    scrollSize = 400 + data.size() * 130;
    currentY = 0;
}

void MatchListScreen::UpdateWidgetListPosition(Vector2D movement) {
    if (currentY + movement.y > scrollSize - 900 || currentY + movement.y < -20) {
        return;
    }
    currentY += movement.y;
    for (auto& widget: widgets) {
        widget.MoveContent(movement);
    }
}

MatchListScreen::MatchListScreen(GameKit& kit, bool& wasClosed, Client& cl, bool& isOwner):
        BaseScreen(kit, wasClosed),
        client(cl),
        header(RectTransform(Vector2D(0, 0), Vector2D(2200, 300), Vector2D(0.5, 1),
                             Vector2D(0.5, 1)),
               ColorExtension::Black(), 3),
        titleText("CREATE A LOBBY", 30,
                  RectTransform(Vector2D(0, -50), Vector2D(500, 160), Vector2D(0.5, 1),
                                Vector2D(0.5, 0.5)),
                  ColorExtension::White(), 4),
        createButton(
                "button_1.png",
                RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                              Vector2D(0.5, 0.5)),
                [this]() { this->OnCreatePressed(); }, Color(40, 40, 40), 4),
        createButtonText("CREATE", 20,
                         RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                                       Vector2D(0.5, 0.5)),
                         ColorExtension::White(), 5),
        joinLobbyText("OR JOIN A LOBBY", 30,
                      RectTransform(Vector2D(-180, -240), Vector2D(500, 160), Vector2D(0.5, 1),
                                    Vector2D(0.5, 0.5)),
                      ColorExtension::White(), 4),
        refreshButton(
                "button_1.png",
                RectTransform(Vector2D(180, -240), Vector2D(250, 80), Vector2D(0.5, 1),
                              Vector2D(0.5, 0.5)),
                [this]() { this->OnRefreshPressed(); }, Color(40, 40, 40), 4),
        refreshButtonText("REFRESH", 20,
                          RectTransform(Vector2D(180, -240), Vector2D(250, 80), Vector2D(0.5, 1),
                                        Vector2D(0.5, 0.5)),
                          ColorExtension::White(), 5),
        controlsButton(
                "button_1.png",
                RectTransform(Vector2D(-85, -45), Vector2D(160, 80), Vector2D(1, 1),
                              Vector2D(0.5, 0.5)),
                [this]() {
                    this->controls.SetActive(true);
                    gameKit.PlayButtonSFX();
                },
                Color(40, 40, 40), 4),
        controlsButtonText("CONTROLS", 20,
                           RectTransform(Vector2D(-85, -45), Vector2D(160, 80), Vector2D(1, 1),
                                         Vector2D(0.5, 0.5)),
                           ColorExtension::White(), 5),
        controls(gameKit),
        playersCountSelection(gameKit),
        isOwner(isOwner) {
    controls.SetActive(false);
}

MatchListScreen::~MatchListScreen() = default;

void MatchListScreen::TakeInput(SDL_Event event) {
    switch (event.type) {
        case SDL_MOUSEWHEEL:
            Vector2D wheelDir = Vector2D::Down() * event.wheel.y;
            UpdateWidgetListPosition(wheelDir * cam.GetRateDeltatime() * 2500);
            break;
    }

    ButtonsManager::GetInstance().HandleEvent(event, cam);
}


void MatchListScreen::InitRun() { WaitRefresh(); }

void MatchListScreen::Update(float deltaTime) {
    TweenManager::GetInstance().Update(deltaTime);
    GUIManager::GetInstance().Draw(cam);
}

#include "MatchListScreen.h"

void MatchListScreen::OnCreatePressed() {
    AudioManager::GetInstance().PlayButtonSFX();

    playersCountSelection.Display([this](uint8_t playersCount) {
        bool createSuccess;
        client.CreateMatch(playersCount);
        LoadingScreen loading(cam, [this, &createSuccess]() {
            std::shared_ptr<ResultJoining> joinResult = nullptr;
            if (client.TryRecvNetworkMsg(joinResult)) {
                createSuccess = joinResult->eCode == 0;
                return true;
            }
            return false;
        });
        loading.Run("Creating match");

        if (createSuccess) {
            isOwner = true;
            running = false;
        }
    });
}

void MatchListScreen::OnJoinLobbyPressed(int id) {
    AudioManager::GetInstance().PlayButtonSFX();

    playersCountSelection.Display([this, id](uint8_t playersCount) {
        bool joinSuccess;
        client.SelectMatch(id, playersCount);
        LoadingScreen loading(cam, [this, &joinSuccess]() {
            std::shared_ptr<ResultJoining> joinResult = nullptr;
            if (client.TryRecvNetworkMsg(joinResult)) {
                joinSuccess = joinResult->eCode == 0;
                return true;
            }
            return false;
        });
        loading.Run("Joining match");

        if (joinSuccess) {
            isOwner = false;
            running = false;
        }
    });
}

void MatchListScreen::OnRefreshPressed() {
    AudioManager::GetInstance().PlayButtonSFX();
    refreshButton.SetInteractable(false);
    client.Refresh();
    WaitRefresh();
    refreshButton.SetInteractable(true);
}

void MatchListScreen::WaitRefresh() {
    LoadingScreen loading(cam, [this]() {
        std::shared_ptr<AvailableMatches> lobbyListResult = nullptr;
        if (client.TryRecvNetworkMsg(lobbyListResult)) {
            LoadWidgetList(lobbyListResult->matches);
            return true;
        }
        return false;
    });
    loading.Run("Getting available lobbies");
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

MatchListScreen::MatchListScreen(Camera& c, Client& cl):
        cam(c),
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
                    AudioManager::GetInstance().PlayButtonSFX();
                },
                Color(40, 40, 40), 4),
        controlsButtonText("CONTROLS", 20,
                           RectTransform(Vector2D(-85, -45), Vector2D(160, 80), Vector2D(1, 1),
                                         Vector2D(0.5, 0.5)),
                           ColorExtension::White(), 5) {
    controls.SetActive(false);
}

MatchListScreen::~MatchListScreen() = default;

bool MatchListScreen::Render() {
    running = true;

    // Get the first available lobbies
    WaitRefresh();

    cam.InitRate();

    while (running) {
        cam.Clean();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_MOUSEWHEEL:
                    Vector2D wheelDir = Vector2D::Down() * event.wheel.y;
                    UpdateWidgetListPosition(wheelDir * cam.GetRateDeltatime() * 2500);
                    break;
            }

            ButtonsManager::GetInstance().HandleEvent(event, cam);
        }

        GUIManager::GetInstance().Draw(cam);
        TweenManager::GetInstance().Update(cam.GetRateDeltatime());

        cam.Render();
        cam.Delay();
    }

    return isOwner;
}

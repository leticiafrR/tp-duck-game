#include "MatchListScreen.h"

void MatchListScreen::OnCreatePressed() {
    audioPlayer.PlayButtonSFX();
    playersCountSelection.Display([this](uint8_t playersCount) {
        bool createSuccess;
        client.CreateMatch(playersCount);
        LoadingScreen loading(
                cam, resource, wasClosed,
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
    audioPlayer.PlayButtonSFX();

    playersCountSelection.Display([this, id](uint8_t playersCount) {
        bool joinSuccess;
        client.SelectMatch(id, playersCount);
        LoadingScreen loading(
                cam, resource, wasClosed,
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
    audioPlayer.PlayButtonSFX();
    refreshButton->SetInteractable(false);
    client.Refresh();
    WaitRefresh();
    refreshButton->SetInteractable(true);
}

void MatchListScreen::WaitRefresh() {
    LoadingScreen loading(
            cam, resource, wasClosed,
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
        widgets.emplace_back(guiManager, lobbyData.matchID, lobbyData.creatorNickname,
                             lobbyData.currentPlayers, lobbyData.maxPlayers,
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

void MatchListScreen::InitHeader() {
    guiManager.CreateImage(
            RectTransform(Vector2D(0, 0), Vector2D(2200, 300), Vector2D(0.5, 1), Vector2D(0.5, 1)),
            3, ColorExtension::Black());

    guiManager.CreateText(RectTransform(Vector2D(0, -50), Vector2D(500, 160), Vector2D(0.5, 1)), 4,
                          "CREATE A LOBBY", 30);

    guiManager.CreateText(RectTransform(Vector2D(-180, -240), Vector2D(500, 160), Vector2D(0.5, 1)),
                          4, "OR JOIN A LOBBY", 30);
}

void MatchListScreen::InitControlsButton() {
    controls.SetActive(false);

    guiManager.CreateButton(RectTransform(Vector2D(-85, -45), Vector2D(160, 80), Vector2D(1, 1)), 4,
                            [this]() {
                                this->controls.SetActive(true);
                                audioPlayer.PlayButtonSFX();
                            });
    guiManager.CreateText(RectTransform(Vector2D(-85, -45), Vector2D(160, 80), Vector2D(1, 1)), 5,
                          "CONTROLS", 20);
}

void MatchListScreen::InitCreateButton() {
    guiManager.CreateButton(RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1)),
                            4, [this]() { this->OnCreatePressed(); });

    guiManager.CreateText(RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1)), 5,
                          "CREATE", 20);
}

void MatchListScreen::InitRefreshButton() {
    refreshButton = guiManager.CreateButton(
            RectTransform(Vector2D(180, -240), Vector2D(250, 80), Vector2D(0.5, 1)), 4,
            [this]() { this->OnRefreshPressed(); });

    guiManager.CreateText(RectTransform(Vector2D(180, -240), Vector2D(250, 80), Vector2D(0.5, 1)),
                          5, "REFRESH", 20);
}

MatchListScreen::MatchListScreen(Camera& cam, ResourceManager& resource, bool& wasClosed,
                                 Client& cl, bool& isOwner):
        BaseScreen(cam, resource, wasClosed),
        client(cl),
        controls(audioPlayer, guiManager),
        playersCountSelection(audioPlayer, guiManager),
        isOwner(isOwner) {

    InitHeader();
    InitControlsButton();
    InitCreateButton();
    InitRefreshButton();
}

MatchListScreen::~MatchListScreen() = default;

void MatchListScreen::TakeInput(SDL_Event event) {
    switch (event.type) {
        case SDL_MOUSEWHEEL:
            Vector2D wheelDir = Vector2D::Down() * event.wheel.y;
            UpdateWidgetListPosition(wheelDir * cam.GetRateDeltatime() * 2500);
            break;
    }

    guiManager.HandleEvent(event, cam);
}

void MatchListScreen::InitRun() { WaitRefresh(); }

void MatchListScreen::Update([[maybe_unused]] float deltaTime) { guiManager.Draw(cam); }

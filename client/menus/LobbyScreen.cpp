#include "LobbyScreen.h"

LobbyScreen::LobbyScreen(Camera& cam, ResourceManager& resource, bool& wasClosed, Client& client,
                         bool isOwner, shared_ptr<MatchStartDto>& matchData):
        BaseScreen(cam, resource, wasClosed),
        client(client),
        isOwner(isOwner),
        matchData(matchData) {

    startButton = guiManager.CreateButton(RectTransform(Vector2D(0, -130), Vector2D(250, 80),
                                                        Vector2D(0.5, 1), Vector2D(0.5, 0.5)),
                                          4, [this]() { OnStartButtonPressed(); });

    startButtonText = guiManager.CreateText(RectTransform(Vector2D(0, -130), Vector2D(250, 80),
                                                          Vector2D(0.5, 1), Vector2D(0.5, 0.5)),
                                            5, "START", 20);

    waitingText = guiManager.CreateText(RectTransform(Vector2D(0, 0), Vector2D(800, 150),
                                                      Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                                        5, "Waiting the host to start the match", 20);
}

LobbyScreen::~LobbyScreen() = default;

void LobbyScreen::OnStartButtonPressed() {
    audioPlayer.PlayButtonSFX();
    startButton->SetInteractable(false);

    client.StartMatch();
    bool startSuccess;
    LoadingScreen loading(
            cam, resource, wasClosed,
            [this, &startSuccess]() {
                std::shared_ptr<ResultStartingMatch> startResult = nullptr;
                if (client.TryRecvNetworkMsg(startResult)) {
                    startSuccess = startResult->success;
                    return true;
                }
                return false;
            },
            "Waiting for server", true);
    loading.Run();

    if (wasClosed)
        return;

    if (!startSuccess) {
        startButton->SetInteractable(true);
    } else {
        waitingToStart = true;
    }
}

void LobbyScreen::InitRun() {
    if (!isOwner) {
        waitingToStart = true;
        startButton->SetVisible(false);
        startButtonText->SetVisible(false);
    }

    waitingText->SetVisible(!isOwner);
}

void LobbyScreen::TakeInput(SDL_Event event) { guiManager.HandleEvent(event, cam); }

void LobbyScreen::Update([[maybe_unused]] float deltaTime) {
    if (waitingToStart) {
        if (client.TryRecvNetworkMsg(matchData)) {
            running = false;
        }
    }

    guiManager.Draw(cam);
}

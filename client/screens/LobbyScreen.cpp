#include "LobbyScreen.h"

LobbyScreen::LobbyScreen(Camera& cam, Client& client, bool isOwner,
                         shared_ptr<MatchStartDto>& matchData):
        BaseScreen(cam),
        client(client),
        isOwner(isOwner),
        matchData(matchData),
        startButton(
                "button_1.png",
                RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                              Vector2D(0.5, 0.5)),
                [this]() { OnStartButtonPressed(); }, Color(40, 40, 40), 4),
        startButtonText("START", 20,
                        RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                                      Vector2D(0.5, 0.5)),
                        ColorExtension::White(), 5),
        waitingTest("Waiting the host to start the match", 45,
                    RectTransform(Vector2D(0, 0), Vector2D(800, 150), Vector2D(0.5, 0.5),
                                  Vector2D(0.5, 0.5)),
                    ColorExtension::White(), 5) {}

LobbyScreen::~LobbyScreen() = default;

void LobbyScreen::OnStartButtonPressed() {
    AudioManager::GetInstance().PlayButtonSFX();
    startButton.SetInteractable(false);

    client.StartMatch();
    bool startSuccess;
    LoadingScreen loading(cam, [this, &startSuccess]() {
        std::shared_ptr<ResultStartingMatch> startResult = nullptr;
        if (client.TryRecvNetworkMsg(startResult)) {
            startSuccess = startResult->success;
            return true;
        }
        return false;
    });
    loading.Run("Waiting for server", true);

    if (!startSuccess) {
        startButton.SetInteractable(true);
    } else {
        waitingToStart = true;
    }
}

void LobbyScreen::InitRun() {
    if (!isOwner) {
        waitingToStart = true;
        startButton.SetVisible(false);
        startButtonText.SetVisible(false);
    }

    waitingTest.SetVisible(!isOwner);
}

void LobbyScreen::TakeInput(SDL_Event event) {
    ButtonsManager::GetInstance().HandleEvent(event, cam);
}

void LobbyScreen::Update(float deltaTime) {
    if (waitingToStart) {
        if (client.TryRecvNetworkMsg(matchData)) {
            running = false;
        }
    }

    TweenManager::GetInstance().Update(deltaTime);
    GUIManager::GetInstance().Draw(cam);
}

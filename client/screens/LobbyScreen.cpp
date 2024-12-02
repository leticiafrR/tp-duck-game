#include "LobbyScreen.h"

LobbyScreen::LobbyScreen(GameKit& kit, bool& wasClosed, Client& client, bool isOwner,
                         shared_ptr<MatchStartDto>& matchData):
        BaseScreen(kit, wasClosed),
        client(client),
        isOwner(isOwner),
        matchData(matchData),
        startButton(
                BUTTON_FILE,
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
    gameKit.PlayButtonSFX();
    startButton.SetInteractable(false);

    client.StartMatch();
    bool startSuccess;
    LoadingScreen loading(
            gameKit, wasClosed,
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

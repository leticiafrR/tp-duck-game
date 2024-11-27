#include "LobbyScreen.h"

LobbyScreen::LobbyScreen(Camera& cam, Client& client, bool isOwner):
        cam(cam), client(client), isOwner(isOwner) {}

LobbyScreen::~LobbyScreen() = default;

std::shared_ptr<MatchStartDto> LobbyScreen::Render() {
    running = true;
    Button startButton(
            "button_1.png",
            RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                          Vector2D(0.5, 0.5)),
            [this, &startButton]() {
                AudioManager::GetInstance().PlayButtonSFX();

                client.StartMatch();
                bool startSuccess;
                startButton.SetInteractable(false);
                std::cout << "Start match!\n";
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
            },
            Color(40, 40, 40), 4);

    Text startButtonText("START", 20,
                         RectTransform(Vector2D(0, -130), Vector2D(250, 80), Vector2D(0.5, 1),
                                       Vector2D(0.5, 0.5)),
                         ColorExtension::White(), 5);

    Text waitingTest("Waiting the host to start the match", 45,
                     RectTransform(Vector2D(0, 0), Vector2D(800, 150), Vector2D(0.5, 0.5),
                                   Vector2D(0.5, 0.5)),
                     ColorExtension::White(), 5);

    if (!isOwner) {
        waitingToStart = true;
        startButton.SetVisible(false);
        startButtonText.SetVisible(false);
    }

    waitingTest.SetVisible(!isOwner);

    cam.InitRate();

    while (running) {
        cam.Clean();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    break;
            }

            ButtonsManager::GetInstance().HandleEvent(event, cam);
        }

        if (waitingToStart) {
            std::shared_ptr<MatchStartDto> matchStart = nullptr;
            if (client.TryRecvNetworkMsg(matchStart)) {
                return matchStart;
            }
        }

        GUIManager::GetInstance().Draw(cam);
        TweenManager::GetInstance().Update(cam.GetRateDeltatime());

        cam.Render();
        cam.Delay();
    }
    return nullptr;
}

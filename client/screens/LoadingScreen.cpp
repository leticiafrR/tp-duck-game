#include "LoadingScreen.h"

LoadingScreen::LoadingScreen(Camera& cam, Function<bool> endFunction):
        cam(cam), endFunction(endFunction) {}

LoadingScreen::~LoadingScreen() = default;

void LoadingScreen::Run(const string& text, bool lockerOnly) {
    Image bg(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)), ColorExtension::Black(), 10);
    Text titleText(text, 60,
                   RectTransform(Vector2D(0, 30), Vector2D(800, 160), Vector2D(0.5, 0.5),
                                 Vector2D(0.5, 0.5)),
                   ColorExtension::White(), 11);

    bg.SetVisible(!lockerOnly);
    bg.SetVisible(!lockerOnly);

    while (true) {
        cam.Clean();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    break;
            }
        }

        if (endFunction()) {
            break;
        }

        GUIManager::GetInstance().Draw(cam);
        cam.Render();
        SDL_Delay(cam.GetRateMiliseconds());
    }
}

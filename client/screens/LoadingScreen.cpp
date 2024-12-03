#include "LoadingScreen.h"

LoadingScreen::LoadingScreen(Camera& cam, ResourceManager& resource, bool& wasClosed,
                             Function<bool> endFunction, const string& text, bool lockerOnly):
        BaseScreen(cam, resource, wasClosed), endFunction(endFunction) {

    guiManager
            .CreateImage(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)), 10,
                         ColorExtension::Black())
            ->SetVisible(!lockerOnly);

    guiManager.CreateText(RectTransform(Vector2D(0, 30), Vector2D(800, 160)), 11, text, 60)
            ->SetVisible(!lockerOnly);
}

LoadingScreen::~LoadingScreen() = default;

void LoadingScreen::InitRun() {}
void LoadingScreen::TakeInput([[maybe_unused]] SDL_Event event) {}
void LoadingScreen::Update([[maybe_unused]] float deltaTime) {
    if (endFunction()) {
        running = false;
    }
    guiManager.Draw(cam);
}

#include "LoadingScreen.h"

LoadingScreen::LoadingScreen(GameKit& kit, bool& wasClosed, Function<bool> endFunction,
                             const string& text, bool lockerOnly):
        BaseScreen(kit, wasClosed),
        bg(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)), ColorExtension::Black(), 10),
        titleText(text, 60,
                  RectTransform(Vector2D(0, 30), Vector2D(800, 160), Vector2D(0.5, 0.5),
                                Vector2D(0.5, 0.5)),
                  ColorExtension::White(), 11),
        endFunction(endFunction) {
    bg.SetVisible(!lockerOnly);
    bg.SetVisible(!lockerOnly);
}

LoadingScreen::~LoadingScreen() = default;

void LoadingScreen::InitRun() {}
void LoadingScreen::TakeInput([[maybe_unused]] SDL_Event event) {}
void LoadingScreen::Update([[maybe_unused]] float deltaTime) {
    if (endFunction()) {
        running = false;
    }
    GUIManager::GetInstance().Draw(cam);
}

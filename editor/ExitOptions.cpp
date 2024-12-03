#include "ExitOptions.h"

#include "createLevel/setLevelName.h"
#include "editLevel/LevelsScreen.h"
#include "editor/constantsEditor.h"
#include "multimedia/gui/ButtonsManager.h"

const int WEIGHT_SCREEN = 940;
const int HIGH_SCREEN = 940;
ExitOptions::ExitOptions(Camera& cam, ResourceManager& resource, bool& wasClosed):
        BaseScreen(cam, resource, wasClosed) {

    background = guiManager.CreateImage(DUCK_BACKGROUND.c_str(),
                                        RectTransform(Vector2D::Zero(), Vector2D(2133, 1200)),
                                        ColorExtension::White(), 0);

    logo = guiManager.CreateImage(DUCK_GAME_LOGO.c_str(),
                                  RectTransform(Vector2D(0, 240), Vector2D(575, 300)));

    exit = guiManager.CreateButton(
            BUTTON_IMAGE_PATH.c_str(),
            RectTransform(Vector2D(-120, -120), Vector2D(300, 150), Vector2D(0.85, 0.65)),
            [this]() {
                exit = true;
                running = false;
            },
            Color(220, 220, 220), 1);

    ExitText = guiManager.CreateText(
            EXIT_LABEL.c_str(), 20,
            RectTransform(Vector2D(-120, -120), Vector2D(400, 400), Vector2D(0.85, 0.65)),
            ColorExtension::White(), 1);

    Menu = guiManager.CreateButton(
            BUTTON_IMAGE_PATH.c_str(),
            RectTransform(Vector2D(-120, -120), Vector2D(300, 150), Vector2D(0.45, 0.65)),
            [this]() {
                exit = false;
                running = false;
            },
            Color(220, 220, 220), 1);

    MenuText = guiManager.CreateText(
            "Back to menu", 20,
            RectTransform(Vector2D(-120, -120), Vector2D(400, 400), Vector2D(0.45, 0.65)),
            ColorExtension::White(), 1);
}

ExitOptions::~ExitOptions() {
    cam.ClearCacheItem(DUCK_BACKGROUND.c_str());
    cam.ClearCacheItem(DUCK_GAME_LOGO.c_str());
}
bool ExitOptions::run() {
    Run();

    if (wasClosed) {
        return QUIT;
    }

    return exit;
}

void ExitOptions::InitRun() {}
void ExitOptions::TakeInput(SDL_Event event) { guiManager.HandleEvent(event, cam); }
void ExitOptions::Update([[maybe_unused]] float deltaTime) { guiManager.Draw(cam); }

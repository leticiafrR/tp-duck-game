#include "MenuScreen.h"

#include "createLevel/setLevelName.h"
#include "editLevel/LevelsScreen.h"
#include "editor/constantsEditor.h"
#include "multimedia/gui/ButtonsManager.h"

const int WEIGHT_SCREEN = 940;
const int HIGH_SCREEN = 940;
MenuScreen::MenuScreen(Camera& cam, ResourceManager& resource, bool& wasClosed):
        BaseScreen(cam, resource, wasClosed), option(CREATE_LVL) {

    guiManager.CreateImage(DUCK_BACKGROUND.c_str(),
                           RectTransform(Vector2D::Zero(), Vector2D(2133, 1200)));

    guiManager.CreateImage(DUCK_GAME_LOGO.c_str(),
                           RectTransform(Vector2D(0, 240), Vector2D(575, 300)));

    guiManager.CreateButton(
            BUTTON_IMAGE_PATH.c_str(),
            RectTransform(Vector2D(-120, -120), Vector2D(300, 150), Vector2D(0.85, 0.65)),
            [this]() {
                option = CREATE_LVL;
                running = false;
            },
            Color(220, 220, 220), 1);

    guiManager.CreateText(
            CREATE_LABEL.c_str(), 20,
            RectTransform(Vector2D(-120, -120), Vector2D(400, 400), Vector2D(0.85, 0.65)),
            ColorExtension::White(), 1);

    guiManager.CreateButton(
            BUTTON_IMAGE_PATH.c_str(),
            RectTransform(Vector2D(-120, -120), Vector2D(300, 150), Vector2D(0.45, 0.65)),
            [this]() {
                option = EDIT_LVL;
                running = false;
            },
            Color(220, 220, 220), 1);

    guiManager.CreateText(
            EDIT_LABEL.c_str(), 20,
            RectTransform(Vector2D(-120, -120), Vector2D(400, 400), Vector2D(0.45, 0.65)),
            ColorExtension::White(), 1);
}

MenuScreen::~MenuScreen() {
    cam.ClearCacheItem(DUCK_BACKGROUND.c_str());
    cam.ClearCacheItem(DUCK_GAME_LOGO.c_str());
}

void MenuScreen::InitRun() {}
void MenuScreen::TakeInput(SDL_Event event) { guiManager.HandleEvent(event, cam); }
void MenuScreen::Update([[maybe_unused]] float deltaTime) { guiManager.Draw(cam); }

int MenuScreen::run() {

    Run();

    if (wasClosed) {
        return QUIT;
    }

    return option;
}

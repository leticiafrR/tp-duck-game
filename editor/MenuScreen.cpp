#include "MenuScreen.h"

#include "createLevel/setLevelName.h"
#include "editLevel/LevelsScreen.h"
#include "editor/constantsEditor.h"
#include "multimedia/gui/ButtonsManager.h"

const int WEIGHT_SCREEN = 940;
const int HIGH_SCREEN = 940;
MenuScreen::MenuScreen(Camera& cam):
        cam(cam),
        background(DUCK_BACKGROUND.c_str(), RectTransform(Vector2D::Zero(), Vector2D(2133, 1200)),
                   ColorExtension::White(), 0),
        logo(DUCK_GAME_LOGO.c_str(), RectTransform(Vector2D(0, 240), Vector2D(575, 300))),
        createLvl(
                BUTTON_IMAGE_PATH.c_str(),
                RectTransform(Vector2D(-120, -120), Vector2D(300, 150), Vector2D(0.85, 0.65)),
                [this]() {
                    option = CREATE_LVL;
                    running = false;
                },
                Color(220, 220, 220), 1),
        textCreateLvl(CREATE_LABEL.c_str(), 20,
                      RectTransform(Vector2D(-120, -120), Vector2D(400, 400), Vector2D(0.85, 0.65)),
                      ColorExtension::White(), 1),
        editLvl(
                BUTTON_IMAGE_PATH.c_str(),
                RectTransform(Vector2D(-120, -120), Vector2D(300, 150), Vector2D(0.45, 0.65)),
                [this]() {
                    option = EDIT_LVL;
                    running = false;
                },
                Color(220, 220, 220), 1),
        textEditLvl(EDIT_LABEL.c_str(), 20,
                    RectTransform(Vector2D(-120, -120), Vector2D(400, 400), Vector2D(0.45, 0.65)),
                    ColorExtension::White(), 1),
        option(CREATE_LVL) {}

MenuScreen::~MenuScreen() {
    cam.ClearCacheItem(DUCK_BACKGROUND.c_str());
    cam.ClearCacheItem(DUCK_GAME_LOGO.c_str());
}
int MenuScreen::run() {
    cam.InitRate();

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    return QUIT;
            }

            ButtonsManager::GetInstance().HandleEvent(event, cam);
        }
        GUIManager::GetInstance().Draw(cam);
        cam.Render();
        cam.Delay();
    }
    return option;
}

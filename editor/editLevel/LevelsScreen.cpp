#include "LevelsScreen.h"

#include "multimedia/gui/ButtonsManager.h"

void LevelsScreen::ReadAvaiableLevels() {
    YAML::Node config = YAML::LoadFile(AVAILABLE_LEVELS_PATH);
    auto platformsList = config[AVAILABLE_LEVELS_STR];
    std::vector<std::string> allPlatformsNames;
    widgets.clear();

    int moveDelta = 130;
    for (std::size_t i = 0; i < platformsList.size(); ++i) {
        std::string platformName = platformsList[i].as<std::string>();
        allPlatformsNames.emplace_back(platformName);
    }
    Vector2D initialPos(0, -100);
    for (std::size_t i = 0; i < allPlatformsNames.size(); ++i) {

        widgets.emplace_back(allPlatformsNames[i], [this](const std::string& name) {
            selectedLvl = name;
            running = false;
        });
        widgets.back().MoveContent(Vector2D::Down() * i * moveDelta + initialPos);
    }
}

LevelsScreen::LevelsScreen(Camera& cam): cam(cam), selectedLvl() { ReadAvaiableLevels(); }
LevelsScreen::~LevelsScreen() { cam.ClearCacheItem(DUCK_BACKGROUND.c_str()); }

void LevelsScreen::UpdateWidgetListPosition(Vector2D movement) {
    /*if (currentY + movement.y > scrollSize - 450 || currentY + movement.y < -10) {
        return;
    }*/
    currentY += movement.y;
    for (auto& widget: widgets) {
        widget.MoveContent(movement);
    }
}
string LevelsScreen::Render(bool lockerOnly) {

    Image bg(DUCK_BACKGROUND.c_str(), RectTransform(Vector2D::Zero(), Vector2D(2133, 1200)),
             ColorExtension::White(), 0);

    bg.SetVisible(!lockerOnly);
    cam.InitRate();
    while (running) {
        cam.Clean();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    return "";
                case SDL_MOUSEWHEEL:
                    Vector2D wheelDir = Vector2D::Down() * event.wheel.y;
                    UpdateWidgetListPosition(wheelDir * cam.GetRateDeltatime() * 2500);
                    break;
            }
            ButtonsManager::GetInstance().HandleEvent(event, cam);
        }
        GUIManager::GetInstance().Draw(cam);
        cam.Render();
        cam.Delay();
    }
    return selectedLvl;
}

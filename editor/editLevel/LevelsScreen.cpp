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

        widgets.emplace_back(guiManager, allPlatformsNames[i], [this](const std::string& name) {
            selectedLvl = name;
            running = false;
        });
        widgets.back().MoveContent(Vector2D::Down() * i * moveDelta + initialPos);
    }
}

LevelsScreen::LevelsScreen(Camera& cam, ResourceManager& resource, bool& wasClosed):
        BaseScreen(cam, resource, wasClosed), selectedLvl() {
    ReadAvaiableLevels();
}
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

    Image* bg = guiManager.CreateImage(DUCK_BACKGROUND.c_str(),
                                       RectTransform(Vector2D::Zero(), Vector2D(2133, 1200)),
                                       ColorExtension::White(), 0);

    bg->SetVisible(!lockerOnly);

    Run();

    if (wasClosed)
        return "";

    return selectedLvl;
}

void LevelsScreen::InitRun() {}

void LevelsScreen::TakeInput(SDL_Event event) {
    switch (event.type) {
        case SDL_MOUSEWHEEL:
            Vector2D wheelDir = Vector2D::Down() * event.wheel.y;
            UpdateWidgetListPosition(wheelDir * cam.GetRateDeltatime() * 2500);
            break;
    }
    guiManager.HandleEvent(event, cam);
}
void LevelsScreen::Update([[maybe_unused]] float deltaTime) { guiManager.Draw(cam); }

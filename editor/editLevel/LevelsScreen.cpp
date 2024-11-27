#include "LevelsScreen.h"

#include "multimedia/gui/ButtonsManager.h"

/*string LevelsScreen::OnSelectLevelPressed(const std::string& name) {
    // AudioManager::GetInstance().PlayButtonSFX();
    std::cout << name << std::endl;
    return name;

}*/

void LevelsScreen::ReadAvaiableLevels() {
    YAML::Node config = YAML::LoadFile(AVAILABLE_LEVELS_PATH);
    auto platformsList = config[AVAILABLE_LEVELS_STR];
    std::vector<std::string> allPlatformsNames;
    widgets.clear();
    Vector2D initialPos(0, -400);
    int moveDelta = 130;
    for (std::size_t i = 0; i < platformsList.size(); ++i) {
        std::string platformName = platformsList[i].as<std::string>();
        allPlatformsNames.emplace_back(platformName);
    }

    for (std::size_t i = 0; i < allPlatformsNames.size(); ++i) {

        widgets.emplace_back(allPlatformsNames[i], [this](const std::string& name) {
            selectedLvl = name;
            running = false;
        });
        widgets.back().MoveContent(Vector2D::Down() * i * moveDelta + initialPos);
    }
}

LevelsScreen::LevelsScreen(Camera& cam): cam(cam), selectedLvl() {}
LevelsScreen::~LevelsScreen() {
    cam.ClearCacheItem(DUCK_BACKGROUND.c_str());
    // cam.ClearCacheItem("duck_game_logo.png");
}


string LevelsScreen::Render(bool lockerOnly) {
    ReadAvaiableLevels();
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
                    exit(0);
                    break;
            }
            ButtonsManager::GetInstance().HandleEvent(event, cam);
        }

        // if (endFunction()) {
        //     break;
        // }

        GUIManager::GetInstance().Draw(cam);
        cam.Render();
        cam.Delay();
    }
    return selectedLvl;
}

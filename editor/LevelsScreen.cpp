#include "LevelsScreen.h"

void LevelsScreen::OnSelectLevelPressed(const std::string& name) {
    // AudioManager::GetInstance().PlayButtonSFX();
    std::cout << name << std::endl;
    // esto no va
    /*playersCountSelection.Display([this, id](uint8_t playersCount) {
        bool joinSuccess;
        client.SelectMatch(id, playersCount);
        LoadingScreen loading(cam, [this, &joinSuccess]() {
            std::shared_ptr<ResultJoining> joinResult = nullptr;
            if (client.TryRecvNetworkMsg(joinResult)) {
                joinSuccess = joinResult->eCode == 0;
                return true;
            }
            return false;
        });
        loading.Run("Joining match");

        if (joinSuccess) {
            isOwner = false;
            running = false;
        }
    });*/
}

void LevelsScreen::ReadAvaiableLevels() {
    std::cout << "Read avaible" << std::endl;
    YAML::Node config = YAML::LoadFile(AVAILABLE_LEVELS_PATH);
    auto platformsList = config[AVAILABLE_LEVELS_STR];
    std::vector<std::string> allPlatformsNames;
    widgets.clear();
    Vector2D initialPos(0, -400);
    int moveDelta = 130;
    for (std::size_t i = 0; i < platformsList.size(); ++i) {
        std::string platformName = platformsList[i].as<std::string>();
        /*for (char c: (RELATIVE_LEVEL_PATH + YAML_FILE)) {
            platformName.erase(std::remove(platformName.begin(), platformName.end(), c),
                               platformName.end());        }*/
        std::cout << platformName << std::endl;
        allPlatformsNames.emplace_back(platformName);
    }

    for (std::size_t i = 0; i < allPlatformsNames.size(); ++i) {

        widgets.emplace_back(allPlatformsNames[i],
                             [this](const std::string& name) { this->OnSelectLevelPressed(name); });
        widgets.back().MoveContent(Vector2D::Down() * i * moveDelta + initialPos);
    }
}

LevelsScreen::LevelsScreen(Camera& cam): cam(cam) {}

std::string LevelsScreen::Render(const string& text, bool lockerOnly) {
    ReadAvaiableLevels();
    Image bg("duck_game_bg.jpg", RectTransform(Vector2D::Zero(), Vector2D(2133, 1200)),
             ColorExtension::White(), 0);
    Text titleText(text, 60,
                   RectTransform(Vector2D(0, 30), Vector2D(800, 160), Vector2D(0.5, 0.5),
                                 Vector2D(0.5, 0.5)),
                   ColorExtension::White(), 11);

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

        // if (endFunction()) {
        //     break;
        // }

        GUIManager::GetInstance().Draw(cam);
        cam.Render();
        SDL_Delay(cam.GetRateMiliseconds());
    }
    return "";
}

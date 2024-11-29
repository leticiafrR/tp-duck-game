#include "EditorScreen.h"

#include "client/tweening/TweenManager.h"

#include "constants.h"
#include "constantsEditor.h"
GroundDto EditorScreen::loadPlatforms(const YAML::Node& config, const std::string& platformName) {

    auto plats = config[platformName];

    float x = 0, y = 0, w = 0, h = 0;
    for (auto fl: plats) {
        string key = fl.first.as<std::string>();
        auto value = fl.second;
        if (key == X_STR) {
            x = value.as<float>();
        } else if (key == Y_STR) {
            y = value.as<float>();
        } else if (key == WEIGHT_STR) {
            w = value.as<float>();
        } else if (key == HIGH_STR) {
            h = value.as<float>();
        }
    }
    // x = 400;
    std::set<VISIBLE_EDGES> edges;
    for (auto edge: plats[EDGES_STR]) {
        std::string edgeStr = edge.as<std::string>();
        if (edgeStr == LEFT_STR)
            edges.insert(LEFT);
        else if (edgeStr == RIGHT_STR)
            edges.insert(RIGHT);
        else if (edgeStr == TOP_STR)
            edges.insert(TOP);
        else if (edgeStr == BOTTOM_STR)
            edges.insert(BOTTOM);
    }
    return GroundDto(Transform(Vector2D(x, y), Vector2D(w, h), 0), edges);
}

vector<GroundDto> EditorScreen::ReadBasicPlataforms() {
    std::vector<GroundDto> grounds;
    YAML::Node config = YAML::LoadFile(OPTIONS_BLOCKS);
    auto platformsList = config[PLATFORMS_STR];
    for (std::size_t i = 0; i < platformsList.size(); ++i) {
        grounds.emplace_back(loadPlatforms(config, platformsList[i].as<string>()));
    }
    return grounds;
}

EditorScreen::EditorScreen(Camera& cam, MapEditor& w):
        cam(cam),
        writer(w),
        saveButton(
                BUTTON_1_IMAGE,
                RectTransform(Vector2D(180, -240), Vector2D(250, 80), Vector2D(0.65, 0.45),
                              Vector2D(0.5, 0.5)),
                [this]() { running = false; }, Color(40, 40, 40), 4),
        saveButtonText(SAVE_LABEL.c_str(), 20,
                       RectTransform(Vector2D(180, -240), Vector2D(250, 80), Vector2D(0.65, 0.45),
                                     Vector2D(0.5, 0.5)),
                       ColorExtension::White(), 5),
        gameMap(cam, w.GetGameScene()) {

    vector<GroundDto> groundBlocks = ReadBasicPlataforms();
    Vector2D initialPos(-20, -150);
    Vector2D initialObj(-30, 22);
    int moveDelta = 40;
    int moveDelta2 = 10;
    for (size_t i = 0; i < groundBlocks.size(); i++) {
        basicsPlatform.emplace_back(groundBlocks[i],
                                    [this](vector<string> edges) { edgesSelected = edges; });
        Vector2D movement = Vector2D::Down() * i * moveDelta + initialPos;
        Vector2D movObj = Vector2D::Down() * i * moveDelta2 + initialObj;
        basicsPlatform.back().MoveContent(movement, movObj);
        basicsPlatform.back().DrawOption(cam);
    }
    scrollSize = 400 + groundBlocks.size() * 130;
}

void EditorScreen::UpdateWidgetListPosition(Vector2D movement) {
    if (currentY + movement.y > scrollSize - 900 || currentY + movement.y < -20) {
        return;
    }
    currentY += movement.y;
    for (auto& widget: basicsPlatform) {
        widget.MoveContent(movement, movement);
    }
}

bool EditorScreen::Render() {
    cam.InitRate();
    GameWorld(cam, writer.GetGameScene()).Run();
    while (running) {
        cam.Clean();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_MOUSEWHEEL:
                    Vector2D wheelDir = Vector2D::Down() * event.wheel.y;
                    UpdateWidgetListPosition(wheelDir * cam.GetRateDeltatime() * 2500);
                    break;
            }

            ButtonsManager::GetInstance().HandleEvent(event, cam);
        }
        for (auto& plt: basicsPlatform) {
            plt.DrawOption(cam);
        }
        GUIManager::GetInstance().Draw(cam);
        // TweenManager::GetInstance().Update(cam.GetRateDeltatime());

        cam.Render();
        cam.Delay();
    }

    return true;
}

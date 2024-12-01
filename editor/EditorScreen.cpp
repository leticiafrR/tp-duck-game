#include "EditorScreen.h"

#include "client/tweening/TweenManager.h"

#include "constants.h"
#include "constantsEditor.h"

using std::pair;
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
                [this]() {
                    running = false;
                    writer.SaveChanges();
                    exit(0);
                },
                Color(40, 40, 40), 4),
        saveButtonText(SAVE_LABEL.c_str(), 20,
                       RectTransform(Vector2D(180, -240), Vector2D(250, 80), Vector2D(0.65, 0.45),
                                     Vector2D(0.5, 0.5)),
                       ColorExtension::White(), 5),
        mapBg(w.GetGameScene().theme, Transform(Vector2D::Zero(), Vector2D(300, 300))),
        playersPoint(
                [this](pair<Object2D, int> _spawnPoint) {
                    spawnPoint = _spawnPoint.first;
                    typeSpawnPoint = _spawnPoint.second;
                },
                PLAYERS_SPAWN_POINT, "white_duck.png", Vector2D(50, -40), string("Player Points"),
                Vector2D(30, 50)),
        collectablesPoint(
                [this](pair<Object2D, int> _spawnPoint) {
                    spawnPoint = _spawnPoint.first;
                    typeSpawnPoint = _spawnPoint.second;
                },
                PLAYERS_SPAWN_POINT, "box.jpg", Vector2D(200, -40), string("Collectables"),
                Vector2D(30, 30)) {
    InitMap(writer.GetGameScene());
    vector<GroundDto> groundBlocks = ReadBasicPlataforms();
    Vector2D initialPos(-200, -100);
    Vector2D initialObj(-200, 300);
    int moveDelta = 100;
    for (size_t i = 0; i < groundBlocks.size(); i++) {
        basicsPlatform.emplace_back(groundBlocks[i],
                                    [this](MapBlock2D blockMap) { selected = blockMap; });
        Vector2D movement = Vector2D::Down() * i * moveDelta + initialPos;
        Vector2D moveObj = Vector2D::Down() * i * moveDelta + initialObj;
        basicsPlatform.back().MoveContent(movement);
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
        widget.MoveContent(movement);
    }
}

void EditorScreen::InitMap(GameSceneDto mapData) {
    for (size_t i = 0; i < mapData.groundBlocks.size(); i++) {
        auto groundData = mapData.groundBlocks[i];
        mapBlocks.emplace_back(BLOCK_MAP, BLOCK_MAP_YAML, groundData.mySpace, 4);

        bool left =
                groundData.visibleEdges.find(VISIBLE_EDGES::LEFT) != groundData.visibleEdges.end();
        bool right =
                groundData.visibleEdges.find(VISIBLE_EDGES::RIGHT) != groundData.visibleEdges.end();
        bool top =
                groundData.visibleEdges.find(VISIBLE_EDGES::TOP) != groundData.visibleEdges.end();
        bool bottom = groundData.visibleEdges.find(VISIBLE_EDGES::BOTTOM) !=
                      groundData.visibleEdges.end();

        mapBlocks[i].SetBorders(left, right, top, bottom);
    }
}

void EditorScreen::DrawGameWorld() {
    mapBg.Draw(cam);

    for (auto& it: mapBlocks) {
        it.Draw(cam);
    }
}

void EditorScreen::DrawOptions() {
    for (auto& plt: basicsPlatform) {
        plt.DrawOption(cam);
    }
}

void EditorScreen::TakeInput() {
    if (selected.has_value()) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        Vector2D worldPos = cam.ScreenToWorldPoint(Vector2D(mouseX, mouseY));
        selected.value().GetTransform().SetPos(worldPos);
    }
    if (spawnPoint.has_value()) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        Vector2D worldPos = cam.ScreenToWorldPoint(Vector2D(mouseX, mouseY));
        spawnPoint.value().GetTransform().SetPos(worldPos);
    }
}

void EditorScreen::HandleMouseClick(const SDL_MouseButtonEvent& event) {
    if (event.button == SDL_BUTTON_LEFT) {
        if (selected.has_value()) {
            int mouseX = event.x;
            int mouseY = event.y;
            Vector2D worldPos = cam.ScreenToWorldPoint(Vector2D(mouseX, mouseY));
            // Lógica para actualizar 'selected' basado en la posición del clic
            MapBlock2D block = selected.value();
            Vector2D size = block.GetTransform().GetSize();
            vector<string> edges = block.GetEdges();
            writer.AddAPlataform(worldPos.x, worldPos.y, size.x, size.y, edges);
            mapBlocks.emplace_back(BLOCK_MAP, BLOCK_MAP_YAML, block.GetTransform(), 4);

            bool left = false, right = false, top = false, bottom = false;

            for (auto& i: edges) {
                if (i == LEFT_STR) {
                    left = true;
                } else if (i == RIGHT_STR) {
                    right = true;
                } else if (i == TOP_STR) {
                    top = true;
                } else if (i == BOTTOM_STR) {
                    bottom = true;
                }
            }
            mapBlocks.back().SetBorders(left, right, top, bottom);
            selected.reset();
        } else if (spawnPoint.has_value()) {
            int mouseX = event.x;
            int mouseY = event.y;
            Vector2D worldPos = cam.ScreenToWorldPoint(Vector2D(mouseX, mouseY));
            if (typeSpawnPoint.value()) {
                writer.AddPlayerSpawnPoint(worldPos.x, worldPos.y);
            } else if (typeSpawnPoint.value() == 1) {
                writer.AddCollectableSpawnPoint(worldPos.x, worldPos.y);
            }
            spawnPoint.reset();
            typeSpawnPoint.reset();
        }
    }
}

bool EditorScreen::Render() {
    cam.InitRate();
    while (running) {
        cam.Clean();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    HandleMouseClick(event.button);
                    break;
                case SDL_MOUSEWHEEL:
                    Vector2D wheelDir = Vector2D::Down() * event.wheel.y;
                    UpdateWidgetListPosition(wheelDir * cam.GetRateDeltatime() * 2500);
                    break;
            }

            ButtonsManager::GetInstance().HandleEvent(event, cam);
        }

        playersPoint.Draw(cam);
        collectablesPoint.Draw(cam);
        DrawOptions();
        DrawGameWorld();
        TakeInput();
        if (selected.has_value()) {
            selected.value().Draw(cam);
        }
        if (spawnPoint.has_value()) {
            spawnPoint.value().Draw(cam);
        }
        GUIManager::GetInstance().Draw(cam);
        // TweenManager::GetInstance().Update(cam.GetRateDeltatime());

        cam.Render();
        cam.Delay();
    }

    return true;
}

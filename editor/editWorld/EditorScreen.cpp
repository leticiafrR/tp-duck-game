#include "EditorScreen.h"

#include <algorithm>
#include <set>

#include "common/Collision.h"
#include "data/gameScene.h"
#include "editor/constantsEditor.h"

#include "constants.h"
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

EditorScreen::EditorScreen(Camera& cam, MapEditor& w, ResourceManager& resourceManager,
                           bool& wasClosed):
        BaseScreen(cam, resourceManager, wasClosed),
        writer(w),
        mapBg(w.GetGameScene().theme, Transform(Vector2D::Zero(), Vector2D(300, 300))),
        playersPoint(
                guiManager,
                [this](pair<Object2D, int> _spawnPoint) {
                    spawnPoint = _spawnPoint.first;
                    typeSpawnPoint = _spawnPoint.second;
                },
                PLAYERS_SPAWN_POINT, WHITE_DUCK.c_str(), Vector2D(50, -40), PLAYER_POINT_LABEL,
                Vector2D(30, 50)),
        collectablesPoint(
                guiManager,
                [this](pair<Object2D, int> _spawnPoint) {
                    spawnPoint = _spawnPoint.first;
                    typeSpawnPoint = _spawnPoint.second;
                },
                COLLECTABLE_SPAWN_POINT, BOX_IMG.c_str(), Vector2D(200, -40),
                COLLECTABLE_POINT_LABEL, Vector2D(30, 30)),
        boxPoint(
                guiManager,
                [this](pair<Object2D, int> _spawnPoint) {
                    spawnPoint = _spawnPoint.first;
                    typeSpawnPoint = _spawnPoint.second;
                },
                BOX_SPAWN_POINT, BOX_IMG.c_str(), Vector2D(-100, -40), BOXES_POINT_LABEL,
                Vector2D(30, 30)) {


    saveButton = guiManager.CreateButton(
            BUTTON_1_IMAGE,
            RectTransform(Vector2D(180, -240), Vector2D(250, 80), Vector2D(0.65, 0.45),
                          Vector2D(0.5, 0.5)),
            [this]() {
                running = false;
                writer.SaveChanges();
                return;
            },
            Color(40, 40, 40), 4);

    saveButtonText = guiManager.CreateText(SAVE_LABEL.c_str(), 20,
                                           RectTransform(Vector2D(180, -240), Vector2D(250, 80),
                                                         Vector2D(0.65, 0.45), Vector2D(0.5, 0.5)),
                                           ColorExtension::White(), 5);

    InitMap(writer.GetGameScene());
    vector<GroundDto> groundBlocks = ReadBasicPlataforms();
    Vector2D initialPos(-200, -100);
    int moveDelta = 100;
    for (size_t i = 0; i < groundBlocks.size(); i++) {
        basicsPlatform.emplace_back(
                guiManager, resourceManager.GetMapThemeData(writer.GetGameScene().theme),
                groundBlocks[i], [this](MapBlock2D blockMap) { selected = blockMap; });
        Vector2D movement = Vector2D::Down() * i * moveDelta + initialPos;

        basicsPlatform.back().MoveContent(movement);
        basicsPlatform.back().DrawOption(cam);
    }
    scrollSize = 400 + groundBlocks.size() * 130;
}

void EditorScreen::UpdateWidgetListPosition(Vector2D movement) {
    currentY += movement.y;
    for (auto& widget: basicsPlatform) {
        widget.MoveContent(movement);
    }
}

void EditorScreen::InitMap(GameSceneDto mapData) {
    for (size_t i = 0; i < mapData.groundBlocks.size(); i++) {
        auto groundData = mapData.groundBlocks[i];
        mapBlocks.emplace_back(resource.GetMapThemeData(writer.GetGameScene().theme),
                               groundData.mySpace);

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
    std::transform(mapData.boxesPoints.begin(), mapData.boxesPoints.end(),
                   std::back_inserter(boxes), [](const auto& box) {
                       return Object2D(BOX_IMG.c_str(), Transform(box.second, Vector2D(2, 2)));
                   });
}

EditorScreen::~EditorScreen() { cam.ClearCacheItem(writer.GetGameScene().theme); }

void EditorScreen::UpdateWorld() {
    mapBlocks.clear();
    InitMap(writer.GetGameScene());
}

void EditorScreen::DrawGameWorld() {
    UpdateWorld();
    mapBg.Draw(cam);
    for (auto& it: mapBlocks) {
        it.Draw(cam);
    }
    for (auto& it: boxes) {
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

void EditorScreen::TakeAPlatform() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    Vector2D worldPos = cam.ScreenToWorldPoint(Vector2D(mouseX, mouseY));
    optional<GroundDto> info = writer.TakePltaform(worldPos);
    if (info.has_value()) {
        selected = MapBlock2D(resource.GetMapThemeData(writer.GetGameScene().theme),
                              info.value().mySpace);
        bool left = false, right = false, top = false, bottom = false;
        set<VISIBLE_EDGES> edges = info.value().visibleEdges;
        for (auto& i: edges) {
            if (i == LEFT) {
                left = true;
            } else if (i == RIGHT) {
                right = true;
            } else if (i == TOP) {
                top = true;
            } else if (i == BOTTOM) {
                bottom = true;
            }
        }
        selected.value().SetBorders(left, right, top, bottom);
    }
}

void EditorScreen::HandleMouseClick(const SDL_MouseButtonEvent& event) {
    if (Collision::RectCollision(saveButton->GetTransform(),
                                 Transform(Vector2D(event.x, event.y), saveButton->GetSize()))) {
        return;
    }
    if (event.button == SDL_BUTTON_LEFT) {
        if (!selected.has_value() && !spawnPoint.has_value()) {
            TakeAPlatform();
        } else {
            if (selected.has_value()) {
                int mouseX = event.x;
                int mouseY = event.y;
                Vector2D worldPos = cam.ScreenToWorldPoint(Vector2D(mouseX, mouseY));
                MapBlock2D block = selected.value();
                Vector2D size = block.GetTransform().GetSize();
                vector<string> edges = block.GetEdges();
                writer.AddAPlataform(worldPos.x, worldPos.y, size.x, size.y, edges);
                mapBlocks.emplace_back(resource.GetMapThemeData(writer.GetGameScene().theme),
                                       block.GetTransform());

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
                if (typeSpawnPoint.value() == PLAYERS_SPAWN_POINT) {
                    writer.AddPlayerSpawnPoint(worldPos.x, worldPos.y);
                } else if (typeSpawnPoint.value() == COLLECTABLE_SPAWN_POINT) {
                    writer.AddCollectableSpawnPoint(worldPos.x, worldPos.y);
                } else if (typeSpawnPoint.value() == BOX_SPAWN_POINT) {
                    writer.AddBoxSpawnPoint(worldPos.x, worldPos.y);
                }
                spawnPoint.reset();
                typeSpawnPoint.reset();
            }
        }
    }
    if (event.button == SDL_BUTTON_RIGHT) {
        selected.reset();
        spawnPoint.reset();
        typeSpawnPoint.reset();
    }
}

bool EditorScreen::Render() {

    Run();

    return !wasClosed;
}


void EditorScreen::InitRun() {}

void EditorScreen::TakeInput(SDL_Event event) {
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            HandleMouseClick(event.button);
            break;
        case SDL_MOUSEWHEEL:
            Vector2D wheelDir = Vector2D::Down() * event.wheel.y;
            UpdateWidgetListPosition(wheelDir * cam.GetRateDeltatime() * 2500);
            break;
    }

    guiManager.HandleEvent(event, cam);
}

void EditorScreen::Update([[maybe_unused]] float deltaTime) {
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

    guiManager.Draw(cam);
}

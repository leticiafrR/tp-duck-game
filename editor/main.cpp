#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "EditorRunner.h"
#include "MenuScreen.h"
#include "constants.h"
#include "constantsEditor.h"
#include "mapEditor.h"

const int WEIGHT_SCREEN = 940;
const int HIGH_SCREEN = 940;

GroundDto loadPlatforms(const YAML::Node& config, const std::string& platformName) {

    auto plats = config[platformName];

    float x = 0, y = 0, w = 0, h = 0;
    for (auto fl: plats) {
        std::string key = fl.first.as<std::string>();
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

std::vector<std::pair<std::string, GroundDto>> ReadBasicPlataforms() {
    std::vector<std::pair<std::string, GroundDto>> grounds;
    YAML::Node config = YAML::LoadFile("../config/basicsGrounds.yaml");
    auto platformsList = config[PLATFORMS_STR];
    for (std::size_t i = 0; i < platformsList.size(); ++i) {
        std::string platformName = platformsList[i].as<std::string>();
        GroundDto ground = loadPlatforms(config, platformName);
        grounds.emplace_back(std::make_pair(platformName, ground));
    }
    return grounds;
}

int main() {
    // std::vector<std::pair<std::string,GroundDto>> grounds= ReadBasicPlataforms();
    SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDLMixer sdlMixer(MIX_INIT_MP3 | MIX_INIT_OGG);
    // AudioManager::GetInstance();
    SDLTTF ttf;

    // Creates a window
    Window window(WINDOW_LABEL.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  WEIGHT_SCREEN, HIGH_SCREEN, SDL_WINDOW_RESIZABLE);

    // Creates a render
    Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
    render.SetDrawBlendMode(SDL_BlendMode::SDL_BLENDMODE_BLEND);  // Allows transparency
    render.SetDrawColor(100, 100, 100, 255);

    // Create a camera with render, 70 camera size(zoom), and 60fps for framerate
    // The Size(zoom) can be update in runtime with cam.SetSize(float)
    EditorRunner editor(render, 60);
    editor.run();
    return 0;
}

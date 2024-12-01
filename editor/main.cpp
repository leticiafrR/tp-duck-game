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

int main() {
    SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDLMixer sdlMixer(MIX_INIT_MP3 | MIX_INIT_OGG);
    // AudioManager::GetInstance();
    SDLTTF ttf;

    Window window(WINDOW_LABEL.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  WEIGHT_SCREEN, HIGH_SCREEN, SDL_WINDOW_RESIZABLE);

    Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
    render.SetDrawBlendMode(SDL_BlendMode::SDL_BLENDMODE_BLEND);  // Allows transparency
    render.SetDrawColor(100, 100, 100, 255);

    EditorRunner editor(render, 60);
    editor.run();
    SDL_Quit();
    return SUCCESS_EXIT;
}

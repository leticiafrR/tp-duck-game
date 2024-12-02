#include <exception>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLTTF.hh>

#include "ClientRunner.h"

using namespace SDL2pp;  // NOLINT

int main() {
    SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDLMixer sdlMixer(MIX_INIT_MP3 | MIX_INIT_OGG);
    SDLTTF ttf;

    Window window("Duck Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 940, 940,
                  SDL_WINDOW_RESIZABLE);

    Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
    render.SetDrawBlendMode(SDL_BlendMode::SDL_BLENDMODE_BLEND);  // Allows transparency
    render.SetDrawColor(100, 100, 100, 255);

    ClientRunner runner(render, 60);
    runner.Run();
    std::cout << "Cerrando el programa correctamente!\n";

    // Verificar
    FontCache::Clear();
    GUIManager::GetInstance().Clear();
}

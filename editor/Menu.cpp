#include "Menu.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "background.h"
#include "button.h"
#include "constantsEditor.h"


const int X_SIZE = 800;
const int Y_SIZE = 600;
Menu::Menu() {}

void Menu::run() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow(WINDOW_LABEL.c_str(), SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, X_SIZE, Y_SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont(PIXEL_FONT.c_str(), 24);
    if (!font) {
        std::cerr << "[MENU] : Error loading font:" << TTF_GetError() << std::endl;
    }
    Background background(DUCK_BACKGROUND.c_str(), renderer);
    Button newLevelButton(200, 200, 200, 50, renderer, font, CREATE_LABEL.c_str(),
                          BUTTON_IMAGE_PATH);
    Button editLevelButton(200, 300, 200, 50, renderer, font, EDIT_LABEL.c_str(),
                           BUTTON_IMAGE_PATH);
    SDL_Event event;
    while (_isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                _isRunning = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (newLevelButton.isClicked(mouseX, mouseY)) {
                    std::cout << "Nuevo Nivel seleccionado" << std::endl;
                    // Lógica para crear nuevo nivel
                } else if (editLevelButton.isClicked(mouseX, mouseY)) {
                    std::cout << "Editar Nivel seleccionado" << std::endl;
                    // Lógica para editar nivel
                }
            }
        }
        SDL_RenderClear(renderer);
        background.render();
        newLevelButton.render();
        editLevelButton.render();
        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

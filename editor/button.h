#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Button {
public:
    Button(int x, int y, int w, int h, SDL_Renderer* ren, TTF_Font* font, const std::string& text,
           const std::string& imagePath);
    ~Button();

    void render();                           // Renderiza el botón en pantalla
    bool isClicked(int mouseX, int mouseY);  // Verifica si el botón fue clickeado
    TTF_Font* getAdjustedFont(int buttonWidth);

private:
    SDL_Rect buttonRect;  // Área del botón
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    std::string label;
    TTF_Font* font;
    SDL_Texture* textTexture;
};

#endif

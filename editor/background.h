#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Background {
public:
    Background(const std::string& filePath, SDL_Renderer* ren);
    ~Background();

    void render();  // Renderiza la imagen de fondo en pantalla

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect destRect;  // Tamaño y posición del fondo (cubrirá toda la pantalla)
};

#endif

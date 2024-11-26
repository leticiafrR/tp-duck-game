#include "background.h"

#include <iostream>

Background::Background(const std::string& filePath, SDL_Renderer* ren): renderer(ren) {
    // Cargar la imagen desde el archivo
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        texture = nullptr;
        return;
    }

    // Crear textura a partir de la superficie
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Error al crear la textura: " << SDL_GetError() << std::endl;
    }

    // Configurar el rectángulo del fondo para cubrir toda la pantalla
    destRect = {0, 0, 800, 600};  // Ajusta a las dimensiones de tu ventana
}

Background::~Background() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Background::render() {
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    }
}

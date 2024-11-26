#include "button.h"

#include <iostream>

#include "constantsEditor.h"

Button::Button(int x, int y, int w, int h, SDL_Renderer* ren, TTF_Font* font,
               const std::string& text, const std::string& imagePath):
        buttonRect(x, y, w, h), renderer(ren), label(text), font(font) {
    // buttonRect = {x, y, w, h};

    SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "[BUTTON]:Error loading button image: " << IMG_GetError() << std::endl;
        texture = nullptr;
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }

    // Crear la textura del texto
    SDL_Color textColor = {255, 255, 255, 255};  // Color blanco para el texto
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, label.c_str(), textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
}

Button::~Button() { SDL_DestroyTexture(texture); }

// Función para ajustar el tamaño de la fuente según el ancho del botón
TTF_Font* Button::getAdjustedFont(int buttonWidth) {
    int fontSize = 24;  // Tamaño de fuente inicial
    TTF_Font* newFont = TTF_OpenFont(PIXEL_FONT.c_str(), fontSize);
    if (!newFont) {
        std::cerr << "Error al cargar la fuente: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    // Intentar ajustar la fuente hasta que el texto encaje
    int textWidth, textHeight;
    while (newFont && TTF_SizeText(newFont, label.c_str(), &textWidth, &textHeight) == 0 &&
           textWidth > buttonWidth) {
        fontSize--;
        if (fontSize <= 8) {
            break;  // No reducir más el tamaño de la fuente
        }
        newFont = TTF_OpenFont(PIXEL_FONT.c_str(), fontSize);
    }

    return newFont;
}
void Button::render() {
    // Renderizar la imagen de fondo del botón
    if (texture) {
        SDL_Rect renderQuad = buttonRect;  // Usar las dimensiones del botón
        SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
    }

    // Ajustar la fuente para que el texto quepa dentro del botón
    if (font) {
        TTF_Font* adjustedFont = getAdjustedFont(buttonRect.w);
        if (!adjustedFont) {
            std::cerr << "Error al ajustar la fuente" << std::endl;
            return;
        }

        SDL_Color textColor = {255, 255, 255, 255};  // Color blanco del texto
        SDL_Surface* textSurface = TTF_RenderText_Solid(adjustedFont, label.c_str(), textColor);

        if (textSurface) {
            // Crear la textura para el texto
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            int textWidth, textHeight;
            TTF_SizeText(adjustedFont, label.c_str(), &textWidth,
                         &textHeight);  // Obtener el tamaño del texto

            // Asegurarse de que el rectángulo del texto esté centrado dentro del botón
            SDL_Rect textRect = {
                    buttonRect.x +
                            (buttonRect.w - textWidth) / 2,  // Centra el texto horizontalmente
                    buttonRect.y +
                            (buttonRect.h - textHeight) / 2,  // Centra el texto verticalmente
                    textWidth,                                // Ancho del texto
                    textHeight                                // Alto del texto
            };

            // Renderizar el texto sobre el botón
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

            // Liberar la textura y superficie del texto
            SDL_DestroyTexture(textTexture);
            SDL_FreeSurface(textSurface);
        }

        // Liberar la fuente ajustada
        TTF_CloseFont(adjustedFont);
    }
}


bool Button::isClicked(int mouseX, int mouseY) {
    return mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
           mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h;
}

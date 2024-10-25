#include <exception>
#include <iostream>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "Collision.h"
#include "Object2D.h"

using namespace SDL2pp;  // NOLINT

int main() try {
    // Initialize SDL library
    SDL sdl(SDL_INIT_VIDEO);

    // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
    Window window("Duck Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 940, 940,
                  SDL_WINDOW_RESIZABLE);

    // Create accelerated video renderer with default driver
    Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
    render.SetDrawColor(100, 100, 100, 255);

    Camera cam(std::move(render), 100);

    cam.CreateObject2D("../client/assets/bg_forest.png",
                       Transform(Vector2D::Zero(), Vector2D(100, 100)));

    Object2D& other = cam.CreateObject2D("../client/assets/bg_city.png",
                                         Transform(Vector2D(8.2, -4.2), Vector2D(5, 5)));
    Object2D& spr = cam.CreateObject2D("../client/assets/img.png",
                                       Transform(Vector2D::Zero(), Vector2D(5, 5)));
    spr.SetColor(Color(255, 255, 255));

    Transform& sprTransform = spr.GetTransform();
    Transform& otherTransform = other.GetTransform();

    bool running = true;

    float speed = 1;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                    switch (keyEvent.keysym.sym) {
                        case SDLK_a:
                            sprTransform.Move(Vector2D::Left() * speed);
                            break;
                        case SDLK_d:
                            sprTransform.Move(Vector2D::Right() * speed);
                            break;
                        case SDLK_w:
                            sprTransform.Move(Vector2D::Up() * speed);
                            break;
                        case SDLK_s:
                            sprTransform.Move(Vector2D::Down() * speed);
                            break;
                    }
                } break;
                case SDL_MOUSEMOTION:
                    // std::cout << "Oh! Mouse" << std::endl;
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        if (Collision::RectCollision(sprTransform, otherTransform)) {
            std::cout << "Collision por recta!"
                      << "\n";
        } else {
            std::cout << "Nada colisionando"
                      << "\n";
        }
        // sprTransform.Rotate(0.1);
        cam.Render();
        SDL_Delay(1);
    }

    // Here all resources are automatically released and library deinitialized
    return 0;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}

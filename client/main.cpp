#include <exception>
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Collision.h"

#include "Animator.h"
#include "Camera.h"
#include "CameraController.h"
#include "Object2D.h"

using namespace SDL2pp;  // NOLINT

#include <set>

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


    cam.CreateObject2D("../client/assets/sprites/bg_forest.png",
                       Transform(Vector2D::Zero(), Vector2D(200, 200)));

    Object2D& other = cam.CreateObject2D("../client/assets/sprites/bg_city.png",
                                         Transform(Vector2D(8.2, -4.2), Vector2D(10, 5)));
    Object2D& spr = cam.CreateObject2D("../client/assets/sprites/base_duck.png",
                                       Transform(Vector2D::Zero(), Vector2D(5, 5)));

    Animator duckAnim("duck.yaml", "idle");

    spr.SetColor(Color(255, 255, 255));

    Transform& sprTransform = spr.GetTransform();
    Transform& otherTransform = other.GetTransform();

    CameraController camController(cam);
    camController.AddTransform(&sprTransform);
    camController.AddTransform(&otherTransform);

    std::set<int> pressedKeysSet;
    bool running = true;
    Vector2D dir = Vector2D::Zero();

    float speed = 1;
    while (running) {
        SDL_Event event;
        duckAnim.SetTarget("idle", false);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;

                    int key = keyEvent.keysym.sym;
                    if (pressedKeysSet.find(key) != pressedKeysSet.end()) {
                        break;
                    }
                    pressedKeysSet.insert(key);

                    switch (keyEvent.keysym.sym) {
                        case SDLK_a:
                            dir += Vector2D::Left();
                            break;
                        case SDLK_d:
                            dir += Vector2D::Right();
                            break;
                        case SDLK_w:
                            dir += Vector2D::Up();
                            break;
                        case SDLK_s:
                            dir += Vector2D::Down();
                            break;
                    }
                } break;
                case SDL_KEYUP: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                    int key = keyEvent.keysym.sym;
                    pressedKeysSet.erase(key);

                    switch (keyEvent.keysym.sym) {
                        case SDLK_a:
                            spr.SetHorizontalFlip(true);
                            dir += Vector2D::Left() * -1;
                            break;
                        case SDLK_d:
                            spr.SetHorizontalFlip(false);
                            dir += Vector2D::Right() * -1;
                            break;
                        case SDLK_w:
                            dir += Vector2D::Up() * -1;
                            break;
                        case SDLK_s:
                            dir += Vector2D::Down() * -1;
                            break;
                    }
                    break;
                }
                case SDL_MOUSEMOTION:
                    // std::cout << "Oh! Mouse" << std::endl;
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        sprTransform.Move(dir * speed);

        if (dir.GetMagnitude() > 0.001) {
            duckAnim.SetTarget("run", false);
        } else {
            duckAnim.SetTarget("idle");
        }

        duckAnim.Update();

        if (dir.x > 0)
            spr.SetHorizontalFlip(false);
        else if (dir.x < 0)
            spr.SetHorizontalFlip(true);

        spr.SetSourceRect(duckAnim.GetTargetRect());

        if (Collision::RectCollision(sprTransform, otherTransform)) {
            Collision::ResolveStaticCollision(sprTransform, otherTransform);
        }

        camController.Update();
        // sprTransform.Rotate(0.1);
        cam.Render();
        SDL_Delay(50);
    }

    // Here all resources are automatically released and library deinitialized
    return 0;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}

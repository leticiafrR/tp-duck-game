#include <exception>
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Collision.h"
#include "common/RigidBody.h"

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
                                         Transform(Vector2D(0, -10), Vector2D(10, 5)));
    Object2D& spr = cam.CreateObject2D("../client/assets/sprites/base_duck.png",
                                       Transform(Vector2D::Zero(), Vector2D(5, 5)));

    Animator duckAnim("duck.yaml", "idle");

    spr.SetColor(Color(255, 255, 255));

    Transform& duckT = spr.GetTransform();
    RigidBody rb(duckT, 8);
    Transform& platformT = other.GetTransform();

    CameraController camController(cam);
    camController.AddTransform(&duckT);
    camController.AddTransform(&platformT);

    std::set<int> pressedKeysSet;
    bool running = true;
    Vector2D dir = Vector2D::Zero();

    int fps = 25;
    float sleepMS = 1000.0f / fps;
    float deltaTime = 1.0f / fps;
    float speed = 0.7f;
    bool isGrounded = false;
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
                        case SDLK_SPACE:
                            if (isGrounded) {
                                rb.ApplyForce(Vector2D::Up() * 40);
                                std::cout << "jump!" << std::endl;
                            }
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
        duckT.Move(dir * speed);

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


        isGrounded = Collision::Raycast(duckT.GetPos(), Vector2D::Down(), 4, platformT);

        rb.Update(deltaTime);

        if (Collision::RectCollision(duckT, platformT)) {
            Collision::ResolveStaticCollision(duckT, platformT);
            if (isGrounded) {
                rb.ResetGravity();
            }
        }

        camController.Update();
        cam.Render();
        SDL_Delay(sleepMS);
    }

    // Here all resources are automatically released and library deinitialized
    return 0;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}

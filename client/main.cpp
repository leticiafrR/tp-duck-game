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
#include "Button.h"
#include "ButtonsManager.h"
#include "Camera.h"
#include "CameraController.h"
#include "MapBlock2D.h"
#include "Object2D.h"
#include "SheetDataCache.h"

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

    Button btn(
            Rect(20, 20, 200, 80),
            []() {
                std::cout << "Button Clicked"
                          << "\n";
            },
            Color(255, 255, 255));

    Object2D bgSpr("bg_forest.png", Transform(Vector2D::Zero(), Vector2D(200, 200)));

    Object2D spr("base_duck.png", Transform(Vector2D::Zero(), Vector2D(5, 5)));

    Object2D akSpr("machine_guns.png", Transform(Vector2D::Zero(), Vector2D(4, 4)));
    akSpr.SetSourceRect(SheetDataCache::GetData("machine_guns.yaml")["ak_47"][0]);

    Animator duckAnim("duck.yaml", "idle", 17);

    MapBlock2D mapBlock("tile_set.png", "tile_set.yaml",
                        Transform(Vector2D(0, -10), Vector2D(40, 20)), 5);

    mapBlock.SetBorders(true, true, true, true);

    spr.SetColor(Color(255, 255, 255));

    Transform& duckT = spr.GetTransform();
    RigidBody rb(duckT, 8);
    Transform& platformT = mapBlock.transform;

    CameraController camController(cam);
    camController.AddTransform(&duckT);
    camController.AddTransform(&platformT);

    std::set<int> pressedKeysSet;
    bool running = true;
    Vector2D dir = Vector2D::Zero();

    int fps = 60;
    float sleepMS = 1000.0f / fps;
    float deltaTime = 1.0f / fps;
    float speed = 15;
    bool isGrounded = false;

    while (running) {
        cam.Clean();
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
                            spr.SetFlip(true);
                            dir += Vector2D::Left() * -1;
                            break;
                        case SDLK_d:
                            spr.SetFlip(false);
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
            ButtonsManager::GetInstance().HandleEvent(event);
        }
        duckT.Move(dir * speed * deltaTime);

        if (dir.GetMagnitude() > 0.001) {
            duckAnim.SetTarget("run", false);
        } else {
            duckAnim.SetTarget("idle");
        }

        duckAnim.Update(deltaTime);

        if (dir.x > 0)
            spr.SetFlip(false);
        else if (dir.x < 0)
            spr.SetFlip(true);

        spr.SetSourceRect(duckAnim.GetTargetRect());


        rb.Update(deltaTime);

        isGrounded = Collision::Raycast(duckT.GetPos(), Vector2D::Down(), 4, platformT);
        if (Collision::RectCollision(duckT, platformT)) {
            Collision::ResolveStaticCollision(duckT, platformT);
            if (isGrounded) {
                rb.ResetGravity();
            }
        }

        bgSpr.Draw(cam);
        mapBlock.Draw(cam);
        spr.Draw(cam);

        akSpr.GetTransform().SetPos(duckT.GetPos() + Vector2D::Down() * 0.8f);
        akSpr.SetFlip(spr.GetFlip());
        akSpr.Draw(cam);

        ButtonsManager::GetInstance().Draw(cam);

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

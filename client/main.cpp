#include <exception>
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLTTF.hh>

#include "common/Collision.h"
#include "common/RigidBody.h"
#include "data/snapshot.h"

#include "Animator.h"
#include "Button.h"
#include "ButtonsManager.h"
#include "Camera.h"
#include "CameraController.h"
#include "ColorExtension.h"
#include "DuckClient.h"
#include "MapBlock2D.h"
#include "Object2D.h"
#include "SheetDataCache.h"
#include "Text.h"
using namespace SDL2pp;  // NOLINT
using namespace std;     // NOLINT

#include <set>

void TestMain(Camera& cam) {
    Object2D bgSpr("bg_forest.png", Transform(Vector2D::Zero(), Vector2D(200, 200)));

    Object2D spr("base_duck.png", Transform(Vector2D::Zero(), Vector2D(5, 5)));

    Object2D akSpr("machine_guns.png", Transform(Vector2D::Zero(), Vector2D(4, 4)));
    akSpr.SetSourceRect(SheetDataCache::GetData("machine_guns.yaml")["ak_47"][0]);

    Animator duckAnim(spr, "duck.yaml", "idle", 17);

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
            // ButtonsManager::GetInstance().HandleEvent(event);
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

        // ButtonsManager::GetInstance().Draw(cam);

        camController.Update();
        cam.Render();
        SDL_Delay(sleepMS);
    }
}

void Menu(Camera& cam) {
    bool running = true;

    Text titleText("DUCK GAME", "pixel.ttf", 160,
                   RectTransform(Transform(Vector2D(0, 160), Vector2D(500, 160)),
                                 Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                   ColorExtension::White());

    Text titleShadow("DUCK GAME", "pixel.ttf", 160,
                     RectTransform(Transform(Vector2D(3, 157), Vector2D(500, 160)),
                                   Vector2D(0.5, 0.5), Vector2D(0.5, 0.5)),
                     ColorExtension::Black());

    Button btn(
            RectTransform(Transform(Vector2D(0, 0), Vector2D(200, 80)), Vector2D(0.5, 0.5),
                          Vector2D(0.5, 0.5)),
            [&running]() { running = false; }, Color(40, 40, 40));

    Text buttonText("START", "pixel.ttf", 30,
                    RectTransform(Transform(Vector2D(0, 0), Vector2D(200, 80)), Vector2D(0.5, 0.5),
                                  Vector2D(0.5, 0.5)),
                    ColorExtension::White());

    int fps = 60;
    float sleepMS = 1000.0f / fps;
    // float deltaTime = 1.0f / fps;

    while (running) {
        cam.Clean();
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    // running = false;
                    break;
            }
            ButtonsManager::GetInstance().HandleEvent(event, cam);
        }

        // Rendering

        ButtonsManager::GetInstance().Draw(cam);
        titleShadow.Draw(cam);
        titleText.Draw(cam);
        buttonText.Draw(cam);
        // cam.DrawText("START", font, Rect(70, 40, 200, 80), ColorExtension::Black());
        cam.Render();
        SDL_Delay(sleepMS);
    }
}

void Game(Camera& cam) {
    CameraController camController(cam);
    // camController.AddTransform(&duckT);

    // Connect to server
    map<int, std::shared_ptr<DuckRenderer>> players;

    // DuckRenderData duck;

    players.emplace(0, std::make_shared<DuckRenderer>());

    // Gameloop
    int fps = 60;
    float sleepMS = 1000.0f / fps;
    float deltaTime = 1.0f / fps;

    std::set<int> pressedKeysSet;

    Object2D bgSpr("bg_forest.png", Transform(Vector2D::Zero(), Vector2D(200, 200)));

    Vector2D next = Vector2D::Zero();

    next += Vector2D(3, 3);
    PlayerEvent ev;
    ev.flipping = Flip::Left;
    ev.motion = Vector2D(5, 5);
    ev.stateTransition = DuckState::RUNNING;
    players[0]->SetEventTarget(ev);

    bool running = true;
    while (running) {
        cam.Clean();
        SDL_Event event;

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
                            // Send to server
                            break;
                        case SDLK_d:
                            // Send to server
                            break;
                        case SDLK_SPACE:
                            // Send to server
                            break;
                    }
                } break;
                case SDL_KEYUP: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                    int key = keyEvent.keysym.sym;
                    pressedKeysSet.erase(key);

                    switch (keyEvent.keysym.sym) {
                        case SDLK_a:
                            // Send to server
                            break;
                        case SDLK_d:
                            // Send to server
                            break;
                    }
                    break;
                }
                case SDL_QUIT:
                    running = false;
                    break;
            }
            // ButtonsManager::GetInstance().HandleEvent(event);
        }

        // Rendering

        bgSpr.Draw(cam);

        for (auto& it: players) {
            auto data = it.second;
            data->Update(deltaTime);
            data->Draw(cam);
        }

        ButtonsManager::GetInstance().Draw(cam);

        camController.Update();
        cam.Render();
        SDL_Delay(sleepMS);
    }
}

int main() try {
    SDL sdl(SDL_INIT_VIDEO);
    Window window("Duck Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 940, 940,
                  SDL_WINDOW_RESIZABLE);
    Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
    render.SetDrawColor(100, 100, 100, 255);
    SDLTTF ttf;

    Camera cam(std::move(render), 100);

    Menu(cam);
    Game(cam);
    // TestMain(cam);

    FontCache::Clear();
    SheetDataCache::Clear();
    //  Here all resources are automatically released and library deinitialized
    return 0;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}

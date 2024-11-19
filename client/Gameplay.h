#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "network/Client.h"
#include "tweening/ImageTween.h"
#include "tweening/TweenManager.h"

#include "BulletRenderer.h"
#include "CameraController.h"
#include "Definitions.h"
#include "DuckClientRenderer.h"
#include "GUIManager.h"
#include "Image.h"
#include "MapBlock2D.h"
#include "Object2D.h"
#include "Rate.h"

using std::list;
using std::map;
using std::set;
using std::shared_ptr;
using std::vector;

class Gameplay {
private:
    Client& client;
    Camera& cam;
    CameraController camController;
    Rate rate;
    Object2D mapBg;

    map<PlayerID_t, std::shared_ptr<DuckClientRenderer>> players;
    vector<MapBlock2D> mapBlocks;
    list<BulletRenderer> bullets;

    set<int> pressedKeysSet;

    bool running = false;
    bool finishing = true;

    void InitPlayers(MatchStartDto matchData, Snapshot firstSnapshot) {
        for (auto& playerData: matchData.playersData) {
            if (firstSnapshot.updates.find(playerData.playerID) == firstSnapshot.updates.end())
                continue;
            Vector2D spawnPos = firstSnapshot.updates[playerData.playerID].motion;

            players.emplace(playerData.playerID, std::make_shared<DuckClientRenderer>(
                                                         Transform(spawnPos, matchData.duckSize),
                                                         playerData.playerSkin, camController));
        }
    }

    void InitMap(GameSceneDto mapData) {
        for (size_t i = 0; i < mapData.groundBlocks.size(); i++) {
            auto groundData = mapData.groundBlocks[i];
            mapBlocks.emplace_back("tile_set.png", "tile_set.yaml", groundData.mySpace, 4);

            bool left = groundData.visibleEdges.find(VISIBLE_EDGES::LEFT) !=
                        groundData.visibleEdges.end();
            bool right = groundData.visibleEdges.find(VISIBLE_EDGES::RIGHT) !=
                         groundData.visibleEdges.end();
            bool top = groundData.visibleEdges.find(VISIBLE_EDGES::TOP) !=
                       groundData.visibleEdges.end();
            bool bottom = groundData.visibleEdges.find(VISIBLE_EDGES::BOTTOM) !=
                          groundData.visibleEdges.end();

            mapBlocks[i].SetBorders(left, right, top, bottom);
        }
    }

    void DrawGame() {
        mapBg.Draw(cam);

        for (auto& it: mapBlocks) {
            it.Draw(cam);
        }

        for (auto& it: bullets) {
            it.Update(rate.GetDeltaTime());
            it.Draw(cam);
        }

        for (const auto& it: players) {
            auto data = it.second;
            data->Update(rate.GetDeltaTime());
            data->Draw(cam);
        }

        GUIManager::GetInstance().Draw(cam);
        cam.Render();
    }

    void BulletsReapDead() {
        bullets.remove_if([](BulletRenderer c) { return !c.IsAlive(); });
    }

    void TakeInput() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    if (finishing)
                        continue;
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;

                    int key = keyEvent.keysym.sym;
                    if (pressedKeysSet.find(key) != pressedKeysSet.end()) {
                        break;
                    }
                    pressedKeysSet.insert(key);

                    switch (keyEvent.keysym.sym) {
                        case SDLK_a:
                            client.TrySendRequest(CommandCode::MoveLeft_KeyDown);
                            break;
                        case SDLK_d:
                            client.TrySendRequest(CommandCode::MoveRight_KeyDown);
                            break;
                        case SDLK_SPACE:
                            client.TrySendRequest(CommandCode::Jump);
                            break;
                        case SDLK_f:
                            client.TrySendRequest(CommandCode::UseItem_KeyDown);
                            break;
                    }
                } break;
                case SDL_KEYUP: {
                    if (finishing)
                        continue;
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                    int key = keyEvent.keysym.sym;
                    pressedKeysSet.erase(key);

                    switch (keyEvent.keysym.sym) {
                        case SDLK_a:
                            client.TrySendRequest(CommandCode::MoveLeft_KeyUp);
                            break;
                        case SDLK_d:
                            client.TrySendRequest(CommandCode::MoveRight_KeyUp);
                            break;
                    }
                    break;
                }
                case SDL_QUIT:
                    exit(0);
                    break;
            }
            // ButtonsManager::GetInstance().HandleEvent(event);
        }
    }

    void TakeSnapshots(Callback OnLastSnapshot) {
        shared_ptr<Snapshot> snapshot;
        while (!finishing && client.TryRecvNetworkMsg(snapshot)) {
            for (size_t i = 0; i < snapshot->raycastsEvents.size(); i++) {
                auto ray = snapshot->raycastsEvents[i];
                bullets.emplace_back(ray.origin, ray.end, 100);
                AudioManager::GetInstance().PlayShootSFX();
            }

            for (const auto& it: snapshot->updates) {
                players[it.first]->SetEventTarget(it.second);
            }
            // Check if last snapshot...
            if (snapshot->gameOver) {
                OnLastSnapshot();
                finishing = true;
            }
        }
    }

public:
    Gameplay(Client& cl, Camera& c, const Rate& r, MatchStartDto matchData, GameSceneDto mapData,
             Snapshot firstSnapshot):
            client(cl),
            cam(c),
            camController(c),
            rate(r),
            mapBg("bg_forest.png", Transform(Vector2D::Zero(), Vector2D(300, 300))) {
        InitPlayers(matchData, firstSnapshot);
        InitMap(mapData);
    }

    void Run() {
        finishing = false;
        running = true;

        Image fadePanel(RectTransform(Transform(Vector2D(0, 0), Vector2D(2000, 2000))),
                        ColorExtension::Black().SetAlpha(0), 10);
        ImageTween fadePanelTween(fadePanel, ColorExtension::Black(), 0.6f,
                                  [this]() { running = false; });

        while (running) {
            cam.Clean();

            TakeInput();
            TakeSnapshots([&fadePanelTween]() { fadePanelTween.Play(); });

            camController.Update();
            TweenManager::GetInstance().Update(rate.GetDeltaTime());

            BulletsReapDead();
            DrawGame();

            SDL_Delay(rate.GetMiliseconds());
        }
    }

    ~Gameplay() = default;
};

#endif

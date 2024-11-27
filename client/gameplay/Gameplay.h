#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "client/gameplay/CameraController.h"
#include "client/gameplay/GameplayGUI.h"
#include "client/network/Client.h"
#include "client/rendering/BulletRenderer.h"
#include "client/rendering/CollectableRenderer.h"
#include "client/rendering/DuckClientRenderer.h"
#include "client/screens/ShowColorsScreen.h"
#include "client/tweening/ImageTween.h"
#include "client/tweening/TweenManager.h"
#include "common/playerIdentifier.h"
#include "multimedia/Definitions.h"
#include "multimedia/GUIManager.h"
#include "multimedia/Image.h"
#include "multimedia/MapBlock2D.h"
#include "multimedia/Object2D.h"

using std::list;
using std::set;
using std::shared_ptr;
using std::unordered_map;
using std::vector;

class Gameplay {
private:
    Client& client;
    Camera& cam;
    CameraController camController;
    Object2D mapBg;

    vector<PlayerData> playersData;
    map<PlayerID_t, std::shared_ptr<DuckClientRenderer>> players;
    vector<MapBlock2D> mapBlocks;
    list<BulletRenderer> bullets;
    unordered_map<CollectableID_t, CollectableRenderer> collectables;

    GameplayGUI gui;

    set<int> pressedKeysSet;

    bool running = false;
    bool finishing = true;

    void InitPlayers(const MatchStartDto& matchData, const Snapshot& firstSnapshot) {
        Vector2D duckSize = matchData.duckSize;
        playersData = matchData.playersData;

        for (auto& pData: playersData) {
            if (firstSnapshot.updates.find(pData.playerID) == firstSnapshot.updates.end())
                continue;
            Vector2D spawnPos = firstSnapshot.updates.at(pData.playerID).motion;
            PlayerEvent initialEvent = firstSnapshot.updates.at(pData.playerID);

            players.emplace(pData.playerID, std::make_shared<DuckClientRenderer>(
                                                    Transform(spawnPos, duckSize), pData,
                                                    initialEvent, camController));
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

    void BulletsReapDead() {
        bullets.remove_if([](BulletRenderer c) { return !c.IsAlive(); });
    }

    void DespawnCollectable(CollectableID_t id) { collectables.erase(id); }
    void SpawnCollectable(CollectableSpawnEventDto collectableData) {
        collectables.emplace(collectableData.id,
                             CollectableRenderer(collectableData.type, collectableData.position));
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
                            std::cout << "A KeyDown\n";
                            client.TrySendRequest(CommandCode::MoveLeft_KeyDown);
                            break;
                        case SDLK_d:
                            std::cout << "D KeyDown\n";
                            client.TrySendRequest(CommandCode::MoveRight_KeyDown);
                            break;
                        case SDLK_SPACE:
                            std::cout << "Space KeyDown\n";
                            client.TrySendRequest(CommandCode::Jump);
                            break;
                        case SDLK_f:
                            std::cout << "F KeyDown\n";
                            client.TrySendRequest(CommandCode::UseItem_KeyDown);
                            break;
                        case SDLK_w:
                            std::cout << "W KeyDown\n";
                            client.TrySendRequest(CommandCode::LookUp_KeyDown);
                            break;
                        case SDLK_s:
                            std::cout << "S KeyDown\n";
                            client.TrySendRequest(CommandCode::Crouch_KeyDown);
                            break;
                        case SDLK_c:
                            std::cout << "C KeyDown\n";
                            client.TrySendRequest(CommandCode::Cuack);
                            break;
                        case SDLK_e:
                            std::cout << "E KeyDown\n";
                            client.TrySendRequest(CommandCode::CollectItem);
                            break;
                        case SDLK_g:
                            std::cout << "G KeyDown\n";
                            client.TrySendRequest(CommandCode::DropItem);
                            break;
                    }

                    if (!players.contains(
                                PlayerIdentifier::GeneratePlayerID(client.getLocalID(), 1)))
                        continue;
                    switch (keyEvent.keysym.sym) {

                        case SDLK_LEFT:
                            std::cout << "Left Arrow KeyDown\n";
                            client.TrySendRequest(CommandCode::MoveLeft_KeyDown, 1);
                            break;
                        case SDLK_RIGHT:
                            std::cout << "Right Arrow KeyDown\n";
                            client.TrySendRequest(CommandCode::MoveRight_KeyDown, 1);
                            break;
                        case SDLK_KP_2:
                            std::cout << "Numpad 2 KeyDown\n";
                            client.TrySendRequest(CommandCode::Jump, 1);
                            break;
                        case SDLK_KP_3:
                            std::cout << "Numpad 3 KeyDown\n";
                            client.TrySendRequest(CommandCode::UseItem_KeyDown, 1);
                            break;
                        case SDLK_UP:
                            std::cout << "Up Arrow KeyDown\n";
                            client.TrySendRequest(CommandCode::LookUp_KeyDown, 1);
                            break;
                        case SDLK_DOWN:
                            std::cout << "Down Arrow KeyDown\n";
                            client.TrySendRequest(CommandCode::Crouch_KeyDown, 1);
                            break;
                        case SDLK_KP_1:
                            std::cout << "Numpad 1 KeyDown\n";
                            client.TrySendRequest(CommandCode::Cuack, 1);
                            break;
                        case SDLK_KP_5:
                            std::cout << "Numpad 5 KeyDown\n";
                            client.TrySendRequest(CommandCode::CollectItem, 1);
                            break;
                        case SDLK_KP_6:
                            std::cout << "Numpad 6 KeyDown\n";
                            client.TrySendRequest(CommandCode::DropItem, 1);
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
                            std::cout << "A KeyUp\n";
                            client.TrySendRequest(CommandCode::MoveLeft_KeyUp);
                            break;
                        case SDLK_d:
                            std::cout << "D KeyUp\n";
                            client.TrySendRequest(CommandCode::MoveRight_KeyUp);
                            break;
                        case SDLK_f:
                            std::cout << "F KeyUp\n";
                            client.TrySendRequest(CommandCode::UseItem_KeyUp);
                            break;
                        case SDLK_w:
                            std::cout << "W KeyUp\n";
                            client.TrySendRequest(CommandCode::LookUp_KeyUp);
                            break;
                        case SDLK_s:
                            std::cout << "S KeyUp\n";
                            client.TrySendRequest(CommandCode::Crouch_KeyUp);
                            break;
                    }

                    if (!players.contains(
                                PlayerIdentifier::GeneratePlayerID(client.getLocalID(), 1)))
                        continue;
                    switch (keyEvent.keysym.sym) {

                        case SDLK_LEFT:
                            std::cout << "Left Arrow KeyUp\n";
                            client.TrySendRequest(CommandCode::MoveLeft_KeyUp, 1);
                            break;
                        case SDLK_RIGHT:
                            std::cout << "Right Arrow KeyUp\n";
                            client.TrySendRequest(CommandCode::MoveRight_KeyUp, 1);
                            break;
                        case SDLK_KP_3:
                            std::cout << "Numpad 3 KeyUp\n";
                            client.TrySendRequest(CommandCode::UseItem_KeyUp, 1);
                            break;
                        case SDLK_UP:
                            std::cout << "Up Arrow KeyUp\n";
                            client.TrySendRequest(CommandCode::LookUp_KeyUp, 1);
                            break;
                        case SDLK_DOWN:
                            std::cout << "Down Arrow KeyUp\n";
                            client.TrySendRequest(CommandCode::Crouch_KeyUp, 1);
                            break;
                    }
                    break;
                }
                case SDL_QUIT:
                    exit(0);
                    break;
            }
        }
    }

    void TakeSnapshots(Callback OnLastSnapshot) {
        shared_ptr<Snapshot> snapshot;
        while (!finishing && client.TryRecvNetworkMsg(snapshot)) {
            for (size_t i = 0; i < snapshot->raycastsEvents.size(); i++) {
                auto ray = snapshot->raycastsEvents[i];
                bullets.emplace_back(ray.type, ray.origin, ray.end, 100);
                AudioManager::GetInstance().PlayShootSFX(ray.type);
            }

            for (const auto& it: snapshot->updates) {
                players[it.first]->SetEventTarget(it.second);
            }

            for (const auto& it: snapshot->collectableSpawns) {
                std::cout << "Collectable spawn\n";
                SpawnCollectable(it);
            }
            for (const auto& it: snapshot->collectableDespawns) {
                std::cout << "Despawn spawn\n";
                DespawnCollectable(it);
            }

            // Check if last snapshot...
            if (snapshot->gameOver) {
                OnLastSnapshot();
                finishing = true;
            }
        }
    }

    void DrawGameWorld() {
        mapBg.Draw(cam);

        for (auto& it: mapBlocks) {
            it.Draw(cam);
        }

        for (auto& it: bullets) {
            it.Update(cam.GetRateDeltatime());
            it.Draw(cam);
        }

        for (const auto& it: players) {
            auto data = it.second;
            data->Update(cam.GetRateDeltatime());
            data->Draw(cam);
        }
    }

    void InitGUI() {
        uint16_t localConnectionId = client.getLocalID();

        bool isPlayer1 = true;
        for (uint8_t i = 0; i < (uint8_t)players.size(); i++) {
            auto playerId = PlayerIdentifier::GeneratePlayerID(localConnectionId, i);

            if (players.contains(playerId)) {
                Color color = players[playerId]->GetSkinColor();
                std::string nickname = players[playerId]->GetNickname();
                if (isPlayer1) {
                    gui.InitPlayer1GUI(color, nickname);
                    isPlayer1 = false;
                } else {
                    gui.InitPlayer2GUI(color, nickname);
                }
            }
        }
    }

public:
    Gameplay(Client& cl, Camera& c, MatchStartDto matchData, GameSceneDto mapData,
             Snapshot firstSnapshot):
            client(cl),
            cam(c),
            camController(c),
            mapBg("bg_forest.png", Transform(Vector2D::Zero(), Vector2D(300, 300))) {
        InitPlayers(matchData, firstSnapshot);
        InitMap(mapData);

        InitGUI();
    }

    void Run(bool isInitial) {
        finishing = false;
        running = true;

        Image fadePanel(RectTransform(Transform(Vector2D(0, 0), Vector2D(2000, 2000))),
                        ColorExtension::Black().SetAlpha(0), 10);
        ImageTween fadePanelTween(fadePanel, ColorExtension::Black().SetAlpha(255), 0.6f,
                                  [this]() { running = false; });

        camController.Reset();

        if (isInitial) {
            ShowColorsScreen(cam, players).Run([this]() { DrawGameWorld(); });
        }

        while (running) {
            cam.Clean();

            TakeInput();
            TakeSnapshots([&fadePanelTween]() { fadePanelTween.Play(); });

            camController.Update(cam.GetRateDeltatime());
            TweenManager::GetInstance().Update(cam.GetRateDeltatime());

            BulletsReapDead();
            DrawGameWorld();
            GUIManager::GetInstance().Draw(cam);

            cam.Render();

            SDL_Delay(cam.GetRateMiliseconds());
        }
    }

    ~Gameplay() = default;
};

#endif

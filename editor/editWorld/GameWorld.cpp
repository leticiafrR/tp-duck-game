#include "GameWorld.h"

#include "constants.h"

void GameWorld::InitMap(GameSceneDto mapData) {
    for (size_t i = 0; i < mapData.groundBlocks.size(); i++) {
        auto groundData = mapData.groundBlocks[i];
        mapBlocks.emplace_back(BLOCK_MAP, BLOCK_MAP_YAML, groundData.mySpace, 4);

        bool left =
                groundData.visibleEdges.find(VISIBLE_EDGES::LEFT) != groundData.visibleEdges.end();
        bool right =
                groundData.visibleEdges.find(VISIBLE_EDGES::RIGHT) != groundData.visibleEdges.end();
        bool top =
                groundData.visibleEdges.find(VISIBLE_EDGES::TOP) != groundData.visibleEdges.end();
        bool bottom = groundData.visibleEdges.find(VISIBLE_EDGES::BOTTOM) !=
                      groundData.visibleEdges.end();

        mapBlocks[i].SetBorders(left, right, top, bottom);
    }
}
/*
void GameWorld::TakeInput() {
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

                if (!World
            ers.contains(PlayerIdentifier::GeneratePlayerID(client.getLocalID(), 1)))
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
                    case SDLK_RSHIFT:
                        std::cout << "R-Shift KeyDown\n";
                        client.TrySendRequest(CommandCode::Jump, 1);
                        break;
                    case SDLK_j:
                        std::cout << "J KeyDown\n";
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
                    case SDLK_o:
                        std::cout << "O KeyDown\n";
                        client.TrySendRequest(CommandCode::Cuack, 1);
                        break;
                    case SDLK_k:
                        std::cout << "K KeyDown\n";
                        client.TrySendRequest(CommandCode::CollectItem, 1);
                        break;
                    case SDLK_l:
                        std::cout << "L KeyDown\n";
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

                if (!World
            ers.contains(PlayerIdentifier::GeneratePlayerID(client.getLocalID(), 1)))
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
                    case SDLK_j:
                        std::cout << "J KeyUp\n";
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

void GameWorld::UpdateGame(const Snapshot& snapshot) {
    for (size_t i = 0; i < snapshot.raycastsEvents.size(); i++) {
        auto ray = snapshot.raycastsEvents[i];
        bullets.emplace_back(ray.type, ray.origin, ray.end, 100);
        AudioManager::GetInstance().PlayShootSFX(ray.type);
    }

    for (const auto& it: snapshot.updates) {
        World
    ers[it.first]->SetEventTarget(it.second);
    }

    for (const auto& it: snapshot.collectableSpawns) {
        std::cout << "Collectable spawn\n";
        SpawnCollectable(it);
    }
    for (const auto& it: snapshot.collectableDespawns) {
        std::cout << "Collectable Despawn\n";
        DespawnCollectable(it);
    }
}


void GameWorld::TakeSnapshots(Callback OnLastSnapshot) {
    shared_ptr<Snapshot> snapshot;
    while (!finishing && client.TryRecvNetworkMsg(snapshot)) {
        UpdateGame(*snapshot);

        // Check if last snapshot...
        if (snapshot->gameOver) {
            OnLastSnapshot();
            finishing = true;
        }
    }
}*/

void GameWorld::DrawGameWorld() {
    mapBg.Draw(cam);

    for (auto& it: mapBlocks) {
        it.Draw(cam);
    }
}

GameWorld::GameWorld(Camera& c, GameSceneDto mapData):
        cam(c),
        // camController(c),
        mapBg(mapData.theme, Transform(Vector2D::Zero(), Vector2D(300, 300))) {
    InitMap(mapData);
    std::cout << mapData.theme << std::endl;
}
GameWorld::~GameWorld() = default;

void GameWorld::Run() {
    finishing = false;
    running = true;

    Image fadePanel(RectTransform(Transform(Vector2D(0, 0), Vector2D(2000, 2000))),
                    ColorExtension::Black().SetAlpha(0), 10);
    // ImageTween fadePanelTween(fadePanel, ColorExtension::Black().SetAlpha(255), 0.6f,
    //                          [this]() { running = false; });

    // camController.Reset();

    cam.InitRate();

    while (running) {
        cam.Clean();

        // TakeInput();
        // TakeSnapshots([&fadePanelTween]() { fadePanelTween.Play(); });

        // camController.Update(cam.GetRateDeltatime());
        // TweenManager::GetInstance().Update(cam.GetRateDeltatime());

        DrawGameWorld();
        GUIManager::GetInstance().Draw(cam);

        cam.Render();

        cam.Delay();

        // SDL_Delay(cam.GetRateMiliseconds());
    }
}

#include "CollectablesController.h"

#include "server/model/weapon/instant/PistolaCowboy.h"
CollectablesController::CollectablesController(ProjectilesController& projectilesController,
                                               const Config& conf,
                                               const std::vector<Vector2D>& weaponSpawnPoints):
        unicID(0),
        weaponSpawnPoints(weaponSpawnPoints),
        conf(conf),
        projectilesController(projectilesController),
        listener(nullptr) {
    std::cout << "was created a pewpewlaser on " << (*weaponSpawnPoints.begin()).ToString() << "\n";
}

Collectable* CollectablesController::PickCollectable(const Transform& collectorSpace,
                                                     TypeCollectable& collectorType) {
    std::cout << "se intenta pickear un collectable\n";
    auto it = std::find_if(collectables.begin(), collectables.end(), [&collectorSpace](auto& pair) {
        return Collision::RectCollision(pair.second->GetTransform(), collectorSpace);
    });

    if (it != collectables.end()) {
        (*it).second->BeCollected(collectorType);
        return DespawnCollectable((*it).first);
    }
    return nullptr;
}

Collectable* CollectablesController::DespawnCollectable(CollectableID_t idDespawn) {
    Collectable* obj = collectables[idDespawn];
    collectables.erase(idDespawn);
    listener->DespawnEvent(idDespawn);
    return obj;
}


void CollectablesController::SpawnCollectable(Collectable* obj) {
    collectables[unicID] = obj;
    listener->SpawnEvent(CollectableSpawnEventDto(unicID, obj->GetTransform().GetPos(),
                                                  obj->GetTypeCollectable()));
    unicID++;
}

/*Hay dos posibles mètodos para agregar un collectable al mapa:Drop o Respawn*/
void CollectablesController::Drop(Collectable* obj, const Vector2D& position) {
    obj->BeDropped(position);
    SpawnCollectable(obj);
    std::cout << "[drop controlller] se logra posicionar en la pos " << position.ToString()
              << std::endl;
}

void CollectablesController::RegisterListener(CollectableEventListener* collectableListener) {
    listener = collectableListener;
}


void CollectablesController::SpawnInitialWeapons() {
    for (auto& p: weaponSpawnPoints) {
        Collectable* obj = new PistolaCowboy(
                projectilesController,
                Transform(p, Vector2D(conf.getDuckSize(), conf.getDuckSize())), conf);
        std::cout << "[CollectablesController::SpawnInitialWeapons] se crea una pistola\n";
        SpawnCollectable(obj);
    }
}

CollectablesController::~CollectablesController() {
    for (auto pair: collectables) {
        delete pair.second;
    }
    collectables.clear();
}

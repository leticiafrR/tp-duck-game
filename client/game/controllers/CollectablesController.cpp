#include "CollectablesController.h"

CollectablesController::CollectablesController(ResourceManager& resourceManager):
        resourceManager(resourceManager) {}

CollectablesController::~CollectablesController() {}

void CollectablesController::SpawnCollectable(CollectableSpawnEventDto collectableData) {
    if (collectables.contains(collectableData.id)) {
        std::cout << "ERROR: este colectable ya existe: " << (int)collectableData.id << "\n";
        return;
    }
    std::cout << "Nuevo colectable con id: " << (int)collectableData.id
              << " y tipo:" << (int)collectableData.type << "\n";

    collectables.emplace(collectableData.id,
                         Collectable(resourceManager.GetCollectableData(collectableData.type),
                                     collectableData.position));
}

void CollectablesController::DespawnCollectable(CollectableID_t id) { collectables.erase(id); }

void CollectablesController::Draw(Camera& cam) {
    for (auto& it: collectables) {
        it.second.Draw(cam);
    }
}

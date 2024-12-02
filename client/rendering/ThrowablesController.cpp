#include "ThrowablesController.h"

ThrowablesController::ThrowablesController(ResourceManager& resourceManager):
        resourceManager(resourceManager) {}
ThrowablesController::~ThrowablesController() = default;

void ThrowablesController::SpawnUpdateThrowable(ThrowableID_t id,
                                                ThrowableSpawnEventDto throwableData) {
    if (throwables.contains(id)) {
        throwables.at(id).SetTargetPos(throwableData.position);
        return;
    }

    throwables.emplace(id, ThrowableRenderer(resourceManager.GetCollectableData(throwableData.type),
                                             throwableData.position));
}

void ThrowablesController::DespawnThrowable(ThrowableID_t id) { throwables.erase(id); }

void ThrowablesController::Draw(float deltaTime, Camera& cam) {
    for (auto& it: throwables) {
        it.second.Update(deltaTime);
        it.second.Draw(cam);
    }
}

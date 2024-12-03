#ifndef THROWABLES_CONTROLLER_H
#define THROWABLES_CONTROLLER_H

#include <unordered_map>

#include "../items/Throwable.h"
#include "client/Framework.h"

using std::unordered_map;

class ThrowablesController {
private:
    ResourceManager& resourceManager;
    unordered_map<ThrowableID_t, Throwable> throwables;

public:
    explicit ThrowablesController(ResourceManager& resourceManager);
    ~ThrowablesController();

    void SpawnUpdateThrowable(ThrowableID_t id, ThrowableSpawnEventDto throwableData);
    void DespawnThrowable(ThrowableID_t id);

    void Draw(float deltaTime, Camera& cam);
};

#endif

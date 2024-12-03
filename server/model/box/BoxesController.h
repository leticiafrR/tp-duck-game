#ifndef BOXES_CONTROLLER_H
#define BOXES_CONTROLLER_H
#include <memory>
#include <optional>
#include <unordered_map>

// #include "server/model/collectable/Collectable.h"
#include "server/model/event/BoxEventListener.h"

#include "Box.h"

class ProjectilesController;
class CollectablesController;
class Config;
class BoxesController {
private:
    CollectablesFactory& factory;
    std::unordered_map<BoxID_t, Box> boxes;
    BoxEventListener* listener;
    void RelaseContent(BoxID_t id, CollectablesController& collectables,
                       ProjectilesController& projectiles);

public:
    explicit BoxesController(const std::unordered_map<BoxID_t, Vector2D>& positionsPerBox,
                             CollectablesFactory& collectablesFactory);
    void RegisterListener(BoxEventListener* l);
    void Update(CollectablesController& collectablesController,
                ProjectilesController& projectilesController);
    std::unordered_map<BoxID_t, Box>& GetBoxes();
};


#endif

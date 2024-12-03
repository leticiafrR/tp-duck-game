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
    std::unordered_map<BoxID_t, Box> boxes;
    BoxEventListener* listener;
    const Config& conf;

public:
    explicit BoxesController(const std::unordered_map<BoxID_t, Vector2D>& positionsPerBox,
                             const Config& conf);
    void RegisterListener(BoxEventListener* l);
    void Explote(Vector2D originExplotion, ProjectilesController& projectiles);
    void DestroyBox(BoxID_t id, CollectablesController& collectables,
                    ProjectilesController& projectiles);
    void Update(CollectablesController& collectables, ProjectilesController& projectiles);
    std::unordered_map<BoxID_t, Box>& GetBoxes();
};


#endif

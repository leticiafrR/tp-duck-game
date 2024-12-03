#include "BoxesController.h"

#include "../physicsConstants.h"
#include "server/config.h"
#include "server/model/collectable/CollectablesController.h"
#include "server/model/projectile/ProjectilesController.h"
#define SCOPE_EXPLOTION 30

#define DAMAGE_EXPLOTION 6
BoxesController::BoxesController(const std::unordered_map<BoxID_t, Vector2D>& positionsPerBox,
                                 const Config& conf):
        listener(nullptr), conf(conf) {
    for (auto& pair: positionsPerBox) {
        // Vector2D pos = pair.second;
        // boxes[pair.first]= Box(pos);
        boxes.emplace(pair.first, Box(pair.second));
    }
}

void BoxesController::RegisterListener(BoxEventListener* l) { listener = l; }

void BoxesController::GenerateExplotion(Vector2D originExplotion,
                                        ProjectilesController& projectiles) {
    Vector2D dir = Vector2D::Right();
    for (int i = 0; i < 10; i++, dir.Rotate(360 / 10)) {
        Projectile* fragment = new Projectile(
                originExplotion, dir, SCOPE_EXPLOTION, DAMAGE_EXPLOTION, TypeProjectile::FRAGMENT,
                projectiles.GetInstantProjectileListener(), INTENSITY_EXPLOTION);
        projectiles.RelaseProjectile(fragment);
    }
}

void BoxesController::DestroyBox(BoxID_t id, CollectablesController& collectables,
                                 ProjectilesController& projectiles) {
    std::optional<std::shared_ptr<Collectable>> maybeContent =
            boxes.find(id)->second.GetContent(projectiles, conf);
    if (maybeContent.has_value()) {
        std::cout << "[BOX destroyed]: contengo algo\n";
        if (maybeContent.value() != nullptr) {
            collectables.AddCollectable(maybeContent.value(), boxes[id].GetTransform().GetPos());
        } else {
            GenerateExplotion(boxes[id].GetTransform().GetPos(), projectiles);
        }
    }
}

void BoxesController::Update(CollectablesController& collectables,
                             ProjectilesController& projectiles) {
    for (auto it = boxes.begin(); it != boxes.end();) {
        if (it->second.IsDead()) {

            std::cout << "una caja habia sido destruida :0 \n";
            DestroyBox(it->first, collectables, projectiles);
            listener->DespawnBox(it->first);
            it = boxes.erase(it);
        } else {
            ++it;
        }
    }
}


std::unordered_map<BoxID_t, Box>& BoxesController::GetBoxes() { return boxes; }

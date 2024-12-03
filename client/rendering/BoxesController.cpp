#include "BoxesController.h"

BoxesController::BoxesController() = default;
BoxesController::~BoxesController() = default;

void BoxesController::SpawnBox(BoxID_t id, Vector2D pos) {
    boxes.emplace(id, Object2D(BOX_FILE, Transform(pos, Vector2D(2, 2))));
}

void BoxesController::DespawnBox(BoxID_t id) { boxes.erase(id); }

void BoxesController::Draw(Camera& cam) {
    for (auto& it: boxes) {
        it.second.Draw(cam);
    }
}

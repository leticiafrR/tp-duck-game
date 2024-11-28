#include "ChestplateRenderer.h"

ChestplateRenderer::ChestplateRenderer(Transform& playerT, Transform transform, int targetFPS):
        Object2D("defense.png", transform),
        playerT(playerT),
        anim(*this, "defense.yaml", "chest_equiped_idle", targetFPS) {}

void ChestplateRenderer::SetAnimTarget(string animTarget, bool resetIndex) {
    if (!anim.TargetExists(animTarget)) {
        anim.SetTarget("chest_equiped_idle", resetIndex);
    }
    anim.SetTarget("chest_equiped_" + animTarget, resetIndex);
}

ChestplateRenderer::~ChestplateRenderer() = default;

void ChestplateRenderer::Update(float deltaTime) {
    transform.SetPos(playerT.GetPos());
    anim.Update(deltaTime);
}

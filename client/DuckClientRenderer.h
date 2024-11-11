#ifndef DUCK_CLIENT_RENDERER_H
#define DUCK_CLIENT_RENDERER_H

#include <map>

#include "common/Transform.h"
#include "data/snapshot.h"

#include "Animator.h"
#include "ColorExtension.h"
#include "Object2D.h"

class DuckClientRenderer {
private:
    const std::map<uint8_t, Color> SkinColors = {
            {0, ColorExtension::White()}, {1, ColorExtension::Yellow()},
            {2, ColorExtension::Blue()},  {3, ColorExtension::Orange()},
            {4, ColorExtension::Cyan()},  {5, ColorExtension::Purple()}};

public:
    Object2D spr;
    Animator anim;

    Vector2D fromPos;
    float tLerp;

    PlayerEvent target;

    DuckClientRenderer(Transform transform, uint8_t colorId):
            spr("base_duck.png", transform),
            anim(this->spr, "duck.yaml", "idle", 17),
            fromPos(transform.GetPos()),
            tLerp(0),
            target() {
        target.stateTransition = DuckState::IDLE;
        target.motion = transform.GetPos();
        spr.SetColor(SkinColors.at(colorId));
        SetEventTarget(target);
    }

    void Update(float deltaTime) {
        tLerp += deltaTime * 13;

        Vector2D pos = Vector2D::Lerp(fromPos, target.motion, tLerp);
        spr.GetTransform().SetPos(pos);
        anim.Update(deltaTime);
    }

    void Draw(Camera& cam) { spr.Draw(cam); }

    void SetEventTarget(PlayerEvent newTarget) {
        fromPos = spr.GetTransform().GetPos();
        tLerp = 0;
        target = newTarget;

        switch (target.stateTransition) {
            case DuckState::IDLE:
                anim.SetTarget("idle");
                break;
            case DuckState::RUNNING:
                anim.SetTarget("run", false);
                break;
            default:
                break;
        }
        spr.SetFlip(target.flipping == Flip::Left);
    }

    ~DuckClientRenderer() {}
};

#endif

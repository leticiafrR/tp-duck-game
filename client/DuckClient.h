#ifndef DUCK_CLIENT_H
#define DUCK_CLIENT_H

#include "common/Transform.h"
#include "data/snapshot.h"

#include "Animator.h"
#include "Object2D.h"

class DuckRenderer {
public:
    Object2D spr;
    Animator anim;

    Vector2D fromPos;
    float tLerp;

    PlayerEvent target;

    DuckRenderer(Transform transform, Color color):
            spr("base_duck.png", transform),
            anim(this->spr, "duck.yaml", "idle", 17),
            fromPos(Vector2D::Zero()),
            tLerp(0),
            target() {
        target.stateTransition = DuckState::IDLE;
        spr.SetColor(color);
        SetEventTarget(target);
    }

    void Update(float deltaTime) {
        spr.GetTransform().SetPos(Vector2D::Lerp(fromPos, target.motion, tLerp));
        tLerp += deltaTime;
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

    ~DuckRenderer() {}
};

#endif

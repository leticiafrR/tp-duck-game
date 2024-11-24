#ifndef DUCK_CLIENT_RENDERER_H
#define DUCK_CLIENT_RENDERER_H

#include <map>
#include <string>

#include "common/Transform.h"
#include "data/snapshot.h"

#include "Animator.h"
#include "AudioManager.h"
#include "ColorExtension.h"
#include "HandItemRenderer.h"
#include "Object2D.h"
#include "Timer.h"

class DuckClientRenderer {
private:
    const std::map<uint8_t, Color> SkinColors = {
            {0, ColorExtension::White()}, {1, ColorExtension::Yellow()},
            {2, ColorExtension::Blue()},  {3, ColorExtension::Orange()},
            {4, ColorExtension::Cyan()},  {5, ColorExtension::Purple()}};

    Timer damagedTimer;
    Color skinColor;
    std::string nickname;
    bool damaged = false;

public:
    CameraController& camController;
    Object2D spr;
    Animator anim;

    Vector2D fromPos;
    float tLerp = 0;

    PlayerEvent target;

    // Object2D pistolSpr;
    HandItemRenderer handItem;

    DuckClientRenderer(const Transform& transform, PlayerData data, PlayerEvent initialEvent,
                       CameraController& camController):
            camController(camController),
            spr("base_duck.png", transform),
            anim(this->spr, "duck.yaml", "idle", 22),
            fromPos(transform.GetPos()),
            target(initialEvent),
            handItem(spr.GetTransform(), initialEvent.typeOnHand) {

        spr.GetTransform().SetSize(transform.GetSize() * 1.4);  // Size rendering offset

        // target.stateTransition = DuckState::IDLE;
        // target.motion = transform.GetPos();
        SetEventTarget(target);
        spr.SetColor(SkinColors.at(data.playerSkin));
        nickname = data.nickname;
        skinColor = spr.GetColor();
        camController.AddTransform(&spr.GetTransform());
    }

    Color GetSkinColor() const { return skinColor; }
    std::string GetNickname() const { return nickname; }

    void Update(float deltaTime) {
        tLerp += deltaTime * 13;

        Vector2D pos = Vector2D::Lerp(fromPos, target.motion, tLerp);
        spr.GetTransform().SetPos(pos);

        if (damaged) {
            anim.SetTarget("damaged");
            damagedTimer.Update(deltaTime);
        }
        anim.Update(deltaTime);

        handItem.Update(target.flipping == Flip::Left, target.isLookingUp);
        // pistolSpr.GetTransform().SetPos(spr.GetTransform().GetPos() + Vector2D::Down() * 0.4f +
        //                                 (Vector2D::Up() * (target.isLookingUp ? 0.6f : 0)));
        // pistolSpr.SetFlip(spr.GetFlip());
    }

    void Draw(Camera& cam) {
        spr.Draw(cam);
        // pistolSpr.Draw(cam);
        handItem.Draw(cam);
    }

    Transform& GetTransform() { return spr.GetTransform(); }

    void OnDamaged() {
        damaged = true;
        spr.SetColor(Color(230, 40, 40));
        damagedTimer = Timer(0.15f, [this]() {
            damaged = false;
            anim.SetTarget("idle");
            spr.SetColor(skinColor);
        });
        AudioManager::GetInstance().PlayDamagedSFX();
        damagedTimer.Start();
    }

    void OnDead() {
        damaged = false;
        anim.SetTarget("dead");
        damagedTimer.Stop();
        spr.SetColor(skinColor);
        // pistolSpr.SetVisible(false);
        handItem.SetVisible(false);

        camController.RemoveTransform(&spr.GetTransform());
    }

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
            case DuckState::JUMPING:
                anim.SetTarget("jumping");
                break;
            case DuckState::FALLING:
                anim.SetTarget("falling");
                break;
            case DuckState::WOUNDED:
                OnDamaged();
                break;
            case DuckState::DEAD:
                OnDead();
                break;
            case DuckState::DEAD_BY_FALLING:
                OnDead();
                break;
            default:
                break;
        }
        spr.SetFlip(target.flipping == Flip::Left);

        // if (newTarget.isLookingUp) {
        //     pistolSpr.GetTransform().SetAngle(target.flipping == Flip::Left ? -90 : 90);
        // } else {
        //     pistolSpr.GetTransform().SetAngle(0);
        // }

        if (newTarget.isCrouched)
            anim.SetTarget("crouched");
    }

    ~DuckClientRenderer() {}
};

#endif

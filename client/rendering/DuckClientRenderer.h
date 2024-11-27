#ifndef DUCK_CLIENT_RENDERER_H
#define DUCK_CLIENT_RENDERER_H

#include <map>
#include <string>

#include "client/gameplay/Animator.h"
#include "client/gameplay/CameraController.h"
#include "client/rendering/HandItemRenderer.h"
#include "client/utils/Timer.h"
#include "common/Transform.h"
#include "data/dataTransferObjects.h"
#include "data/snapshot.h"
#include "multimedia/2d/Object2D.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/audio/AudioManager.h"

class DuckClientRenderer {
private:
    static const std::map<uint8_t, Color> SkinColors;

    Timer damagedTimer;
    Timer cuackTimer;
    Color skinColor;
    std::string nickname;
    bool damaged = false;
    bool cuack = false;

public:
    CameraController& camController;
    Object2D spr;
    Animator anim;

    Vector2D fromPos;
    float tLerp = 0;

    PlayerEvent target;

    HandItemRenderer handItem;

    DuckClientRenderer(const Transform& transform, PlayerData data, PlayerEvent initialEvent,
                       CameraController& camController);
    ~DuckClientRenderer();

    static Color GetColorById(uint8_t id);

    Color GetSkinColor() const;
    std::string GetNickname() const;

    void Update(float deltaTime);

    void Draw(Camera& cam);

    Transform& GetTransform();

    void OnCuack();

    void OnDamaged();

    void OnDead();

    string GetAnimAndCuack(string anim);
    void SetEventTarget(PlayerEvent newTarget);
};

#endif

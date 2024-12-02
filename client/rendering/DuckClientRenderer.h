#ifndef DUCK_CLIENT_RENDERER_H
#define DUCK_CLIENT_RENDERER_H

#include <map>
#include <string>

#include "client/Framework.h"
#include "client/gameplay/CameraController.h"
#include "client/rendering/HandItemRenderer.h"
#include "data/dataTransferObjects.h"
#include "data/snapshot.h"

#include "ChestplateRenderer.h"
#include "HelmetRenderer.h"

class DuckClientRenderer: public Object2D {
private:
    Timer damagedTimer;
    Timer cuackTimer;
    Color skinColor;
    std::string nickname;
    bool damaged = false;
    bool cuack = false;

public:
    DuckData duckData;
    CameraController& camController;
    Animator anim;

    Vector2D fromPos;
    float tLerp = 0;

    PlayerEvent target;

    HandItemRenderer handItem;

    ChestplateRenderer armor;
    HelmetRenderer helmet;

    DuckClientRenderer(Vector2D size, Color skinColor, ResourceManager& resourceManager,
                       CameraController& camController);

    ~DuckClientRenderer();

    Color GetSkinColor() const;
    std::string GetNickname() const;

    void Update(float deltaTime);

    void Draw(Camera& cam) override;

    Transform& GetTransform();

    void OnCuack(AudioManager& audioManager);

    void OnDamaged(AudioManager& audioManager);

    void OnDead();

    void SetTargetAnimation(const string& animTarget, bool resetIndex = true);

    string GetAnimAndCuack(string animTarget);

    void SetEventTarget(PlayerEvent newTarget, ResourceManager& resourceManager,
                        AudioManager& audioManager, bool initial = false);
};

#endif

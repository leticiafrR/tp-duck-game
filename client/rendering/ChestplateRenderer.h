#ifndef CHEST_PLATE_RENDERER_H
#define CHEST_PLATE_RENDERER_H

#include <string>

#include "client/gameplay/Animator.h"
#include "multimedia/2d/Object2D.h"

using std::string;

class ChestplateRenderer: public Object2D {
private:
    Transform& playerT;
    Animator anim;

public:
    ChestplateRenderer(Transform& playerT, Transform transform, int targetFPS);

    void SetAnimTarget(string animTarget, bool resetIndex = true);

    void Update(float deltaTime);

    ~ChestplateRenderer();
};

#endif

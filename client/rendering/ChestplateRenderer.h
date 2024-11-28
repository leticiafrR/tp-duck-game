#ifndef CHEST_PLATE_RENDERER_H
#define CHEST_PLATE_RENDERER_H

#include <string>

#include "client/Framework.h"

using std::string;

class ChestplateRenderer: public Object2D {
private:
    Transform& playerT;
    Animator anim;

public:
    ChestplateRenderer(Transform& playerT, int targetFPS);

    void SetAnimTarget(string animTarget, bool resetIndex = true);

    void Update(float deltaTime, bool flip);

    ~ChestplateRenderer();
};

#endif

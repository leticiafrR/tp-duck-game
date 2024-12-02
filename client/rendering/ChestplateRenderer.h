#ifndef CHEST_PLATE_RENDERER_H
#define CHEST_PLATE_RENDERER_H

#include <string>

#include "client/Framework.h"

using std::string;

const string ARMOR_DEFAULT_FRAME = "armor_idle";
const string ARMOR_FRAME_PREFIX = "armor_";

class ChestplateRenderer: public Object2D {
private:
    Transform& playerT;
    Animator anim;

public:
    ChestplateRenderer(Transform& playerT, ArmorData data, int targetFPS);

    void SetAnimTarget(string animTarget, bool resetIndex = true);

    void Update(float deltaTime, bool flip);

    ~ChestplateRenderer();
};

#endif

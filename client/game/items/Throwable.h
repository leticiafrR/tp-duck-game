#ifndef THROWABLE_H
#define THROWABLE_H

#include <unordered_map>

#include "client/Framework.h"

using std::unordered_map;

class Throwable: public Object2D {
private:
    Vector2D fromPos;
    Vector2D targetPos;
    float tLerp;

public:
    Throwable(CollectableData data, Vector2D target);

    void SetTargetPos(Vector2D target);

    void Update(float deltaTime);

    ~Throwable();
};

#endif

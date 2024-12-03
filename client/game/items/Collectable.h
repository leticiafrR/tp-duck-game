#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <unordered_map>

#include "client/Framework.h"
#include "data/snapshot.h"

using std::unordered_map;

class Collectable: public Object2D {
private:
public:
    Collectable(CollectableData data, Vector2D position);

    ~Collectable();
};

#endif

#ifndef HAND_ITEM_H
#define HAND_ITEM_H
#include <string>
#include <unordered_map>

#include "client/Framework.h"
#include "data/snapshot.h"

using std::string;
using std::unordered_map;

class HandItem: public Object2D {
private:
    Transform& playerT;
    float angle;
    const Vector2D offset = Vector2D(0, -0.4f);

public:
    explicit HandItem(Transform& playerT, CollectableData data = CollectableData());
    ~HandItem();

    void SetItem(CollectableData type);

    void Update(bool playerFlip, bool lookingUp);
};

#endif

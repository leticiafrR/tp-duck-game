#ifndef TRANSFORM_FOLLOW
#define TRANSFORM_FOLLOW

#include "common/Transform.h"

class TransformFollow {
private:
    Transform& follower;
    Transform& target;
    Vector2D offset;

public:
    TransformFollow(Transform& followerT, Transform& targetT, Vector2D offset = Vector2D::Zero());
    ~TransformFollow();

    void Follow();
};


#endif

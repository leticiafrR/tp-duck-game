#include "TransformFollow.h"

TransformFollow::TransformFollow(Transform& followerT, Transform& targetT, Vector2D offset):
        follower(followerT), target(targetT), offset(offset) {
    Follow();
}
TransformFollow::~TransformFollow() = default;

void TransformFollow::Follow() { follower.SetPos(target.GetPos() + offset); }

void TransformFollow::SetOffset(Vector2D offset) { this->offset = offset; }

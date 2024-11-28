#include "TransformFollow.h"

TransformFollow::TransformFollow(Transform& followerT, Transform& targetT, Vector2D offset):
        follower(followerT), target(targetT), offset(offset) {}

void TransformFollow::Follow() { follower.SetPos(target.GetPos() + offset); }

TransformFollow::~TransformFollow() = default;

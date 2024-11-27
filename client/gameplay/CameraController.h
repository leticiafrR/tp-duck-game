#ifndef ZOOM_CONTROLLER
#define ZOOM_CONTROLLER

#include <algorithm>
#include <list>

#include "multimedia/Camera.h"

class CameraController {
private:
    Camera& camera;
    float minSize;
    std::list<Transform*> transforms;

    Vector2D minLimit = Vector2D(-1000, -1000);
    Vector2D maxLimit = Vector2D(1000, 1000);

    void CalculateCorners(Vector2D& minCorner, Vector2D& maxCorner);

public:
    explicit CameraController(Camera& camera, float minSize = 35);
    ~CameraController();

    void AddTransform(Transform* transform);

    void RemoveTransform(Transform* transform);

    float MoveSizeTowards(float current, float target, float maxDelta);

    void Reset();

    void Update(float deltaTime);
};

#endif

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

    void CalculateCorners(Vector2D& minCorner, Vector2D& maxCorner) {

        for (auto& t: transforms) {
            Vector2D pos = t->GetPos();
            Vector2D size = t->GetSize();

            if (pos.x - size.x / 2 < minCorner.x) {
                minCorner.x = pos.x - size.x / 2;
            }
            if (pos.x + size.x / 2 > maxCorner.x) {
                maxCorner.x = pos.x + size.x / 2;
            }
            if (pos.y - size.y / 2 < minCorner.y) {
                minCorner.y = pos.y - size.y / 2;
            }
            if (pos.y + size.y / 2 > maxCorner.y) {
                maxCorner.y = pos.y + size.y / 2;
            }
        }
    }

public:
    explicit CameraController(Camera& camera, float minSize = 35):
            camera(camera), minSize(minSize) {}
    ~CameraController() = default;

    void AddTransform(Transform* transform) { transforms.push_back(transform); }

    void RemoveTransform(Transform* transform) { transforms.remove(transform); }

    float MoveSizeTowards(float current, float target, float maxDelta) {
        if (std::abs(target - current) <= maxDelta) {
            return target;
        } else {
            if (target > current)
                return current + maxDelta;
            else
                return current - maxDelta;
        }
    }

    void Reset() {
        Vector2D minCorner;
        Vector2D maxCorner;

        CalculateCorners(minCorner, maxCorner);

        float offset = 5.5;
        camera.SetPos((minCorner + maxCorner) / 2);

        Vector2D total = maxCorner - minCorner;
        float size = std::max(total.x, total.y) + offset;

        if (size < minSize)
            size = minSize;
        camera.SetSize(size);
    }

    void Update(float deltaTime) {
        if (transforms.size() == 0)
            return;

        Vector2D minCorner;
        Vector2D maxCorner;

        CalculateCorners(minCorner, maxCorner);

        if (!minCorner.IsFarFrom(maxCorner, 0.001f))
            return;

        float offset = 5.5;
        Vector2D targetPos =
                Vector2D::MoveTowards(camera.GetPos(), (minCorner + maxCorner) / 2, 25 * deltaTime);
        camera.SetPos(targetPos);

        Vector2D total = maxCorner - minCorner;
        float size = MoveSizeTowards(camera.GetSize(), std::max(total.x, total.y) + offset,
                                     25 * deltaTime);

        if (size < minSize)
            size = minSize;
        camera.SetSize(size);
    }
};

#endif

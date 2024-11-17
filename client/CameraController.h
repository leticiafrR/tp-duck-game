#ifndef ZOOM_CONTROLLER
#define ZOOM_CONTROLLER

#include <list>

#include "Camera.h"

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

    void Update() {
        if (transforms.size() == 0)
            return;

        Vector2D minCorner;
        Vector2D maxCorner;

        CalculateCorners(minCorner, maxCorner);

        if (!minCorner.IsFarFrom(maxCorner, 0.001f))
            return;

        float offset = 5.5;

        camera.SetPos((minCorner + maxCorner) / 2);
        float size = Vector2D::Distance(minCorner, maxCorner) + offset;
        if (size < minSize)
            size = minSize;
        camera.SetSize(size);

        // Vector2D total = maxPos - minPos;
        // camera.SetSize(std::max(total.x, total.y) + offset);
    }
};

#endif

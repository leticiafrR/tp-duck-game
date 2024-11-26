#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <algorithm>
#include <vector>

#include "Camera.h"
#include "GraphicUI.h"

class GUIManager {
private:
    GUIManager() = default;
    std::vector<GraphicUI*> graphics;

public:
    static GUIManager& GetInstance() {
        static GUIManager Instance;
        return Instance;
    }

    void AddGUI(GraphicUI* gui) {
        graphics.push_back(gui);
        CheckSort();
    }

    void RemoveGUI(GraphicUI* gui) {
        auto it = std::find(graphics.begin(), graphics.end(), gui);
        if (it != graphics.end()) {
            graphics.erase(it);
        }

        CheckSort();
    }


    void CheckSort() {
        bool sorted = std::is_sorted(
                graphics.begin(), graphics.end(),
                [](GraphicUI* a, GraphicUI* b) { return a->GetLayerOrder() < b->GetLayerOrder(); });

        if (!sorted) {
            std::sort(graphics.begin(), graphics.end(), [](GraphicUI* a, GraphicUI* b) {
                return a->GetLayerOrder() < b->GetLayerOrder();
            });
        }
    }
    // void HandleEvent(const SDL_Event& e, Camera& cam) {
    //     int mouseX, mouseY;
    //     SDL_GetMouseState(&mouseX, &mouseY);

    //     for (auto btn: buttons) {
    //         btn->HandleEvent(e, mouseX, mouseY, cam);
    //     }
    // }

    const std::vector<GraphicUI*>& GetGraphics() { return graphics; }

    void Draw(Camera& cam) {
        for (auto gui: graphics) {
            if (!gui->GetVisible())
                continue;
            gui->Draw(cam);
        }
    }

    // Remove copy
    GUIManager(const GUIManager&) = delete;
    GUIManager& operator=(const GUIManager&) = delete;

    ~GUIManager() = default;
};

#endif

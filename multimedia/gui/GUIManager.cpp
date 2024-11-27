#include "GUIManager.h"

GUIManager::GUIManager() = default;
GUIManager::~GUIManager() = default;

GUIManager& GUIManager::GetInstance() {
    static GUIManager Instance;
    return Instance;
}

const std::vector<GraphicUI*>& GUIManager::GetGraphics() { return graphics; }

void GUIManager::AddGUI(GraphicUI* gui) {
    graphics.push_back(gui);
    CheckSort();
}

void GUIManager::RemoveGUI(GraphicUI* gui) {
    auto it = std::find(graphics.begin(), graphics.end(), gui);
    if (it != graphics.end()) {
        graphics.erase(it);
    }
    CheckSort();
}

void GUIManager::CheckSort() {
    bool sorted = std::is_sorted(graphics.begin(), graphics.end(), [](GraphicUI* a, GraphicUI* b) {
        return a->GetLayerOrder() < b->GetLayerOrder();
    });

    if (!sorted) {
        std::sort(graphics.begin(), graphics.end(), [](GraphicUI* a, GraphicUI* b) {
            return a->GetLayerOrder() < b->GetLayerOrder();
        });
    }
}

void GUIManager::Draw(Camera& cam) {
    for (auto gui: graphics) {
        if (!gui->GetVisible())
            continue;
        gui->Draw(cam);
    }
}

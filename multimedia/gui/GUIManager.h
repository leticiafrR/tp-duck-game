#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <algorithm>
#include <vector>

#include "multimedia/Camera.h"

#include "GraphicUI.h"

class GUIManager {
private:
    std::vector<GraphicUI*> graphics;

    GUIManager();
    ~GUIManager();

public:
    static GUIManager& GetInstance();

    const std::vector<GraphicUI*>& GetGraphics();

    void AddGUI(GraphicUI* gui);

    void RemoveGUI(GraphicUI* gui);

    void CheckSort();

    void Draw(Camera& cam);

    // Remove copy
    GUIManager(const GUIManager&) = delete;
    GUIManager& operator=(const GUIManager&) = delete;

    void Clear() { graphics.clear(); }
};

#endif

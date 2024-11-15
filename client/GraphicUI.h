#ifndef GRAPHIC_UI_H
#define GRAPHIC_UI_H

#include "Camera.h"

class GraphicUI {
private:
    int layerOrder = 0;
    bool visible = true;

public:
    explicit GraphicUI(int layerOrder = 0);

    virtual ~GraphicUI();

    virtual void Draw(Camera& cam) = 0;

    void SetLayerOrder(int layerOrder);
    int GetLayerOrder();

    void SetVisible(bool visible);
    bool GetVisible();
};

#endif

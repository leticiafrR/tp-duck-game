#ifndef GRAPHIC_UI_H
#define GRAPHIC_UI_H

#include "Camera.h"
#include "RectTransform.h"

class GraphicUI {
protected:
    RectTransform rect;
    int layerOrder = 0;
    bool canTarget = true;
    bool visible = true;

public:
    explicit GraphicUI(RectTransform rect, int layerOrder = 0);

    virtual ~GraphicUI();

    virtual void Draw(Camera& cam) = 0;

    void SetLayerOrder(int layerOrder);
    int GetLayerOrder();

    void SetVisible(bool visible);
    bool GetVisible();

    void SetCanTarget(bool target);
    bool GetCanTarget();

    RectTransform& GetRectTransform();
};

#endif

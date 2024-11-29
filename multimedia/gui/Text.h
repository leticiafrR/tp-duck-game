#ifndef TEXT_H
#define TEXT_H

#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLTTF.hh>

#include "multimedia/Camera.h"
#include "multimedia/cache/FontCache.h"

#include "GraphicUI.h"
#include "RectTransform.h"

using std::string;
using namespace SDL2pp;  // NOLINT

class Text: public GraphicUI {
private:
    string text = "";
    string filename = "pixel.ttf";
    int fontSize = 0;

public:
    Text(const string& text, int fontSize, const RectTransform& rect, Color color,
         int layerOrder = 0, const string& filename = "pixel.ttf");

    ~Text();

    void SetText(const string& newText);

    Font& GetFont();

    void Draw(Camera& cam) override;
};

#endif
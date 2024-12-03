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

const string DEFAULT_TTF = "pixel.ttf";

class Text: public GraphicUI {
private:
    string text = "";
    string filename = DEFAULT_TTF;
    int fontSize = 0;

public:
    Text(const RectTransform& rect = RectTransform(), int layerOrder = 0,
         Color color = ColorExtension::White(), const string& filename = DEFAULT_TTF);

    Text(const string& text, int fontSize, const RectTransform& rect,
         Color color = ColorExtension::White(), int layerOrder = 0,
         const string& filename = DEFAULT_TTF);

    ~Text();

    void SetText(const string& newText);
    void SetFontSize(int fontSize);

    void SetActive(bool active) override;

    void SetTextAndFontSize(const string& newText, int fontSize);

    void Draw(Camera& cam) override;
};

#endif

#include "Text.h"

Text::Text(const RectTransform& rect, int layerOrder, Color color, const string& filename):
        GraphicUI(rect, color, layerOrder), text(""), filename(filename), fontSize(0) {
    SetCanTarget(false);
}

Text::Text(const string& text, int fontSize, const RectTransform& rect, Color color, int layerOrder,
           const string& filename):
        GraphicUI(rect, color, layerOrder), text(text), filename(filename), fontSize(fontSize) {
    SetCanTarget(false);
}

Text::~Text() = default;

void Text::SetText(const string& newText) { text = newText; }
void Text::SetFontSize(int fontSize) { this->fontSize = fontSize; }
void Text::SetTextAndFontSize(const string& newText, int fontSize) {
    SetText(newText);
    SetFontSize(fontSize);
}

void Text::Draw(Camera& cam) {
    if (text.size() == 0 || !visible) {
        return;
    }
    cam.DrawText(text, filename, fontSize, rect, color);
}

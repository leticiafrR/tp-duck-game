#ifndef SHOW_COLORS_SCREEN_H
#define SHOW_COLORS_SCREEN_H

#include <memory>
#include <vector>

#include "client/rendering/DuckClientRenderer.h"
#include "client/tweening/ImageTween.h"
#include "client/tweening/TweenManager.h"
#include "client/utils/Timer.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/Definitions.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Image.h"
#include "multimedia/gui/Text.h"

using std::make_shared;
using std::shared_ptr;
using std::vector;

class DuckColorItemGUI {
private:
    Image imgColor;
    Text txtNickname;

public:
    DuckColorItemGUI(Vector2D pos, const DuckClientRenderer& duck);
    void SetActive(bool active);
    ~DuckColorItemGUI();
};


class ShowColorsScreen {
private:
    Image bg;
    ImageTween bgTween;
    Timer timer;

    bool finished;

    vector<shared_ptr<DuckColorItemGUI>> ducksGUI;

public:
    ShowColorsScreen();

    void Show(map<PlayerID_t, shared_ptr<DuckClientRenderer>>& ducks);
    void Update(float deltaTime);

    void Finish();
    bool HasFinished();

    ~ShowColorsScreen();
};

#endif

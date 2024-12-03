#ifndef SHOW_COLORS_PANEL_H
#define SHOW_COLORS_PANEL_H

#include <list>
#include <unordered_map>

#include "client/Framework.h"
#include "client/FrameworkUI.h"
#include "data/dataTransferObjects.h"

using std::list;
using std::unordered_map;

class DuckColorItemGUI {
private:
    Image* imgColor;
    Text* txtNickname;

public:
    DuckColorItemGUI(GUIManager& guiManager, Vector2D pos, const PlayerData& playerData,
                     DuckData duckData);
    void SetActive(bool active);
    ~DuckColorItemGUI();
};


class ShowColorsScreen {
private:
    GUIManager& guiManager;

    Image* bg;
    ImageTween bgTween;
    Timer timer;

    bool finished;

    list<DuckColorItemGUI> ducksGUI;

public:
    explicit ShowColorsScreen(GUIManager& guiManager);

    void Show(const unordered_map<PlayerID_t, PlayerData>& playersData, DuckData duckData);

    void Update(float deltaTime);

    void Finish();
    bool HasFinished();

    ~ShowColorsScreen();
};

#endif

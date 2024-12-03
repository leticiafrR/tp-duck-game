#ifndef PLAYERS_COUNT_PANEL_H
#define PLAYERS_COUNT_PANEL_H

#include <vector>

#include "multimedia/audio/AudioManager.h"
#include "multimedia/gui/GUIManager.h"

class PlayersCountSelection {
private:
    vector<GraphicUI*> items;

    CallbackParam<uint8_t> onSelection;

    void InitPanel(AudioManager& audioPlayer, GUIManager& guiManager);
    void InitOnePlayerButton(AudioManager& audioPlayer, GUIManager& guiManager);
    void InitSecondPlayerButton(AudioManager& audioPlayer, GUIManager& guiManager);

public:
    explicit PlayersCountSelection(AudioManager& audioPlayer, GUIManager& guiManager);

    ~PlayersCountSelection();

    void Display(CallbackParam<uint8_t> onSelection);

    void Hide();

    void SetActive(bool active);
};

#endif

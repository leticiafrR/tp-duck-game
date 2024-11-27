#ifndef PLAYERS_COUNT_SELECTION_H
#define PLAYERS_COUNT_SELECTION_H

#include "multimedia/Definitions.h"
#include "multimedia/audio/AudioManager.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/Text.h"

class PlayersCountSelection {
private:
    Image imgBglocker;
    Image imgBg;

    Button btnBack;

    Text txtTitle;

    Button btnOnePlayer;
    Text txtOnePlayer;

    Button btnTwoPlayers;
    Text txtTwoPlayers;

    CallbackParam<uint8_t> onSelection;

public:
    PlayersCountSelection();

    ~PlayersCountSelection();

    void Display(CallbackParam<uint8_t> onSelection);

    void Hide();

    void SetActive(bool active);
};

#endif

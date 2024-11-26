#ifndef MENU_H
#define MENU_H

#include "background.h"
#include "button.h"

class Menu {
private:
    bool _isRunning = true;

public:
    Menu();
    void run();
};
#endif

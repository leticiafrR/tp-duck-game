#include "EditorRunner.h"

#include <string>

#include "createLevel/setLevelName.h"
#include "editLevel/LevelsScreen.h"

#include "EditorScreen.h"
#include "MenuScreen.h"
using std::string;

EditorRunner::EditorRunner(Renderer& render, int fps): cam(std::move(render), 70, Rate(fps)) {}
void EditorRunner::run() {
    bool option = MenuScreen(cam).run();

    string lvlName;
    if (option) {
        SetLevelName newLvl(cam);
        lvlName = newLvl.Render();
    } else {
        LevelsScreen listLvls(cam);
        lvlName = listLvls.Render();
    }
    std::cout << lvlName << std::endl;
    MapEditor writeArchive(lvlName);
    EditorScreen runner(cam, writeArchive);
    bool b = runner.Render();
    std::cout << b << std::endl;
}

#include "EditorRunner.h"

#include <string>

#include "createLevel/setLevelName.h"
#include "editLevel/LevelsScreen.h"

#include "MenuScreen.h"
using std::string;
void EditorRunner::run(Camera& cam) {
    // Camera  cam(std::move(render), 70, Rate(60));
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
}

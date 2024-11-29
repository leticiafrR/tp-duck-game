#include "EditorRunner.h"

#include <string>

#include "createLevel/setLevelName.h"
#include "editLevel/LevelsScreen.h"

#include "EditorScreen.h"
#include "MenuScreen.h"
using std::string;

EditorRunner::EditorRunner(Renderer& render, int fps): cam(std::move(render), 70, Rate(fps)) {}
void EditorRunner::run() {
    int option = MenuScreen(cam).run();
    if (option == QUIT) {
        return;
    } else if (option == CREATE_LVL) {
        SetLevelName newLvl(cam);
        writeArchive.AddFileName(newLvl.Render());
    } else {
        LevelsScreen listLvls(cam);
        writeArchive = MapEditor(listLvls.Render());
    }

    EditorScreen runner(cam, writeArchive);
    bool b = runner.Render();
    std::cout << b << std::endl;
    writeArchive.SaveChanges();
}

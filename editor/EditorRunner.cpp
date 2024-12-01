#include "EditorRunner.h"

#include <string>

#include "createLevel/setLevelName.h"
#include "editLevel/LevelsScreen.h"
#include "editWorld/EditorScreen.h"

#include "ExitOptions.h"
#include "MenuScreen.h"
using std::string;

EditorRunner::EditorRunner(Renderer& render, int fps): cam(std::move(render), 70, Rate(fps)) {}
void EditorRunner::run() {
    bool exit = false;
    while (!exit) {
        MapEditor writeArchive;
        int option = MenuScreen(cam).run();
        if (option == QUIT) {
            return;
        } else if (option == CREATE_LVL) {
            SetLevelName newLvl(cam);
            writeArchive.AddFileName(newLvl.Render());
        } else {
            LevelsScreen listLvls(cam);
            string name = listLvls.Render();
            if (name == "") {
                return;
            }
            writeArchive = MapEditor(name);
        }
        EditorScreen runner(cam, writeArchive);
        if (!runner.Render()) {
            return;
        }
        exit = ExitOptions(cam).run();
    }
}

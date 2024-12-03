#include "EditorRunner.h"

#include <string>

#include "createLevel/setLevelName.h"
#include "editLevel/LevelsScreen.h"
#include "editWorld/EditorScreen.h"
#include "selectTheme/themesScreen.h"

#include "ExitOptions.h"
#include "MenuScreen.h"
using std::string;

EditorRunner::EditorRunner(Renderer& render, int fps): cam(std::move(render), 70, Rate(fps)) {}
void EditorRunner::run() {
    bool exit = false;
    bool wasClosed = false;
    ResourceManager resource;

    while (!exit) {
        MapEditor writeArchive;
        int option = MenuScreen(cam, resource, wasClosed).run();
        if (option == QUIT) {
            return;
        } else if (option == CREATE_LVL) {
            SetLevelName newLvl(cam, resource, wasClosed);
            writeArchive.AddFileName(newLvl.Render());
            writeArchive.AddTheme(ThemesScreen(cam, resource, wasClosed).Render());
        } else {
            LevelsScreen listLvls(cam, resource, wasClosed);
            string name = listLvls.Render();
            if (name == "") {
                return;
            }
            writeArchive = MapEditor(name);
            writeArchive.AddTheme(ThemesScreen(cam, resource, wasClosed).Render());
        }
        EditorScreen runner(cam, writeArchive, resource, wasClosed);
        if (!runner.Render()) {
            return;
        }
        exit = ExitOptions(cam, resource, wasClosed).run();
    }
}

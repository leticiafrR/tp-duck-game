#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "constants.h"
#include "constantsEditor.h"
#include "mapEditor.h"

// Se encarga de crear o guardar los cambios y settear el nombre del nivel en la lista
void NewFile() {
    MapEditor editor;

    editor.AddFileName("pepeArgento");

    editor.AddPlayerSpawnPoint(1, 1);
    editor.AddPlayerSpawnPoint(0, 0);
    std::vector<std::string> edges = {"TOP", "BOTTOM", "LEFT", "RIGHT"};
    editor.AddAPlataform(1, 1, 1, 1, edges);
    editor.AddAPlataform(2, 2, 2, 2, edges);

    editor.SaveChanges();
}

void EditFile() {
    MapEditor editor("../config/levels/pepeArgento.yaml");

    editor.AddPlayerSpawnPoint(1, 1);
    editor.AddPlayerSpawnPoint(0, 0);
    std::vector<std::string> edges = {"TOP", "BOTTOM", "LEFT", "RIGHT"};
    editor.AddAPlataform(3, 3, 3, 3, edges);
    editor.AddAPlataform(4, 4, 4, 4, edges);
    editor.ModificateAPlataform("plataform_0", 8, 8, 8, 8, edges);

    editor.SaveChanges();
}

int main() {
    NewFile();
    EditFile();
    return 0;
}

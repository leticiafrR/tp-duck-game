#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "constants.h"
#include "constantsEditor.h"
#include "mapEditor.h"

// Se encarga de crear o guardar los cambios y vectortear el nombre del nivel en la lista
void NewFile() {
    MapEditor editor;

    editor.AddFileName("pepeArgento");

    editor.AddPlayerSpawnPoint(0, 8);
    editor.AddPlayerSpawnPoint(3, 8);
    std::vector<std::string> edges = {"TOP", "BOTTOM", "LEFT", "RIGHT"};
    editor.AddAPlataform(0, 0, 8, 8, edges);
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
    editor.ModificateAPlataform("platform_0", 8, 8, 8, 8, edges);
    editor.DeleteAPlataform("platform_1");

    editor.SaveChanges();
}

void BasicGrounds() {
    MapEditor editor;
    editor.AddFileName("bascisGrounds");

    std::vector<std::string> all = {"TOP", "BOTTOM", "LEFT", "RIGHT"};
    std::vector<std::string> t = {"TOP"};
    std::vector<std::string> b = {"BOTTOM"};
    std::vector<std::string> l = {"LEFT"};
    std::vector<std::string> r = {"RIGHT"};
    std::vector<std::string> tb = {"TOP", "BOTTOM"};
    std::vector<std::string> tl = {"TOP", "LEFT"};
    std::vector<std::string> tr = {"TOP", "RIGHT"};
    std::vector<std::string> bl = {"BOTTOM", "LEFT"};
    std::vector<std::string> br = {"BOTTOM", "RIGHT"};
    std::vector<std::string> lr = {"LEFT", "RIGHT"};
    std::vector<std::string> tbl = {"TOP", "BOTTOM", "LEFT"};
    std::vector<std::string> tbr = {"TOP", "BOTTOM", "RIGHT"};
    std::vector<std::string> tlr = {"TOP", "LEFT", "RIGHT"};
    std::vector<std::string> blr = {"BOTTOM", "LEFT", "RIGHT"};

    editor.AddAPlataform(0, 0, 8, 8, all);
    editor.AddAPlataform(0, 0, 8, 8, t);
    editor.AddAPlataform(0, 0, 8, 8, b);
    editor.AddAPlataform(0, 0, 8, 8, l);
    editor.AddAPlataform(0, 0, 8, 8, r);
    editor.AddAPlataform(0, 0, 8, 8, tb);
    editor.AddAPlataform(0, 0, 8, 8, tl);
    editor.AddAPlataform(0, 0, 8, 8, tr);
    editor.AddAPlataform(0, 0, 8, 8, bl);
    editor.AddAPlataform(0, 0, 8, 8, br);
    editor.AddAPlataform(0, 0, 8, 8, lr);
    editor.AddAPlataform(0, 0, 8, 8, tbl);
    editor.AddAPlataform(0, 0, 8, 8, tbr);
    editor.AddAPlataform(0, 0, 8, 8, tlr);
    editor.AddAPlataform(0, 0, 8, 8, blr);

    editor.SaveChanges();
}
int main() {
    // NewFile();
    // EditFile();
    BasicGrounds();
    return 0;
}

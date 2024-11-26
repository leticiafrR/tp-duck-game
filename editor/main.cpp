#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "constants.h"
#include "constantsEditor.h"
#include "mapEditor.h"

// Se encarga de crear o guardar los cambios y vectortear el nombre del nivel en la lista
void NewFile() {
    MapEditor editor;

    editor.AddFileName("lionelMessi");

    editor.AddPlayerSpawnPoint(0, 8);
    editor.AddPlayerSpawnPoint(3, 8);
    std::vector<std::string> edges = {"TOP", "BOTTOM", "LEFT", "RIGHT"};
    editor.AddAPlataform(0, 0, 8, 8, edges);
    editor.AddAPlataform(2, 2, 2, 2, edges);
    editor.AddAPlataform(0, 0, 8, 8, edges);
    // editor.AddAPlataform(0, 0, 8, 8, t);
    // editor.AddAPlataform(0, 0, 8, 8, b);
    // editor.AddAPlataform(0, 0, 8, 8, l);
    // editor.AddAPlataform(0, 0, 8, 8, r);
    // editor.AddAPlataform(0, 0, 8, 8, tb);
    // editor.AddAPlataform(0, 0, 8, 8, tl);
    // editor.AddAPlataform(0, 0, 8, 8, tr);
    // editor.AddAPlataform(0, 0, 8, 8, bl);
    // editor.AddAPlataform(0, 0, 8, 8, br);
    // editor.AddAPlataform(0, 0, 8, 8, lr);
    // editor.AddAPlataform(0, 0, 8, 8, tbl);
    // editor.AddAPlataform(0, 0, 8, 8, tbr);
    // editor.AddAPlataform(0, 0, 8, 8, tlr);
    // editor.AddAPlataform(0, 0, 8, 8, blr);
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

GroundDto loadPlatforms(const YAML::Node& config, const std::string& platformName) {

    auto plats = config[platformName];

    float x = 0, y = 0, w = 0, h = 0;
    for (auto fl: plats) {
        std::string key = fl.first.as<std::string>();
        auto value = fl.second;
        if (key == X_STR) {
            x = value.as<float>();
        } else if (key == Y_STR) {
            y = value.as<float>();
        } else if (key == WEIGHT_STR) {
            w = value.as<float>();
        } else if (key == HIGH_STR) {
            h = value.as<float>();
        }
    }
    std::set<VISIBLE_EDGES> edges;
    for (auto edge: plats[EDGES_STR]) {
        std::string edgeStr = edge.as<std::string>();
        if (edgeStr == LEFT_STR)
            edges.insert(LEFT);
        else if (edgeStr == RIGHT_STR)
            edges.insert(RIGHT);
        else if (edgeStr == TOP_STR)
            edges.insert(TOP);
        else if (edgeStr == BOTTOM_STR)
            edges.insert(BOTTOM);
    }
    return GroundDto(Transform(Vector2D(x, y), Vector2D(w, h), 0), edges);
}

std::vector<std::pair<std::string, GroundDto>> ReadBasicPlataforms() {
    std::vector<std::pair<std::string, GroundDto>> grounds;
    YAML::Node config = YAML::LoadFile("../config/basicsGrounds.yaml");
    auto platformsList = config[PLATFORMS_STR];
    for (std::size_t i = 0; i < platformsList.size(); ++i) {
        std::string platformName = platformsList[i].as<std::string>();
        GroundDto ground = loadPlatforms(config, platformName);
        grounds.emplace_back(std::make_pair(platformName, ground));
    }
    return grounds;
}

void PrintBasicGrounds(std::vector<std::pair<std::string, GroundDto>> gr) {
    for (const auto& it: gr) {
        Transform t = it.second.mySpace;
        Vector2D p = t.GetPos();
        Vector2D s = t.GetSize();
        std::cout << "Name: " << it.first << "\nx: " << p.x << ", y: " << p.y << "\nweight: " << s.x
                  << " ,high: " << s.y << std::endl;
    }
}
int main() {
    // NewFile();
    // EditFile();
    // BasicGrounds();
    // std::vector<std::pair<std::string,GroundDto>> grounds= ReadBasicPlataforms();
    // PrintBasicGrounds(grounds);
    return 0;
}

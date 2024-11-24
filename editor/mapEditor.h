#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "constants.h"
#include "constantsEditor.h"

class MapEditor {
private:
    YAML::Node config;
    int plataformsCounter;
    std::string fileName;

public:
    MapEditor();
    explicit MapEditor(const std::string& filePath);

    void AddFileName(const std::string& fileName);
    void AddAPlataform(const float& x, const float& y, const float& w, const float& h);
    void SaveChanges();
    void AddPlayerSpawnPoint(const float& x, const float& y);
    void AddWeaponSpawnPoint(const float& x, const float& y);
    void AddBoxSpawnPoint(const float& x, const float& y);
};
#endif

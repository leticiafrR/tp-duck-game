#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "data/gameScene.h"

#include "constants.h"
#include "constantsEditor.h"

class MapEditor {
private:
    YAML::Node config;
    int platformsCounter;
    std::string fileName;
    std::string filePath;

public:
    MapEditor();
    explicit MapEditor(const std::string& fileName);

    void AddFileName(const std::string& fileName);
    void AddAPlataform(const float& x, const float& y, const float& w, const float& h,
                       const std::vector<std::string>& edges);
    void SaveChanges();
    void AddPlayerSpawnPoint(const float& x, const float& y);
    void AddWeaponSpawnPoint(const float& x, const float& y);
    void AddBoxSpawnPoint(const float& x, const float& y);
    void AddTheme(const std::string& theme);
    void AddFullMapSize(const size_t& x, const size_t& y);
    void DeleteALevel();
    void ModificateAPlataform(const std::string& plataformName, const float& x, const float& y,
                              const float& w, const float& h,
                              const std::vector<std::string>& edges);
    void DeleteAPlataform(const std::string& plataformName);
    std::vector<GroundDto> GetPlataforms();
    // faltan implementar
};
#endif

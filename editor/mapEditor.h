#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "data/gameScene.h"
#include "multimedia/ThemeInfo.h"

#include "constants.h"
#include "constantsEditor.h"

using std::set;
using std::string;
using std::vector;
class MapEditor {
private:
    YAML::Node config;
    int platformsCounter;
    string fileName;
    string filePath;
    ThemeInfo parser;

public:
    MapEditor();
    explicit MapEditor(const string& fileName);

    void AddFileName(const string& fileName);
    void AddAPlataform(const float& x, const float& y, const float& w, const float& h,
                       const vector<string>& edges);
    void SaveChanges();
    void AddPlayerSpawnPoint(const float& x, const float& y);
    void AddCollectableSpawnPoint(const float& x, const float& y);
    void AddTheme(const string& theme);
    void AddFullMapSize(const size_t& x, const size_t& y);
    void DeleteALevel();
    void ModificateAPlataform(const string& plataformName, const float& x, const float& y,
                              const float& w, const float& h, const vector<string>& edges);
    void DeleteAPlataform(const string& plataformName);
    vector<GroundDto> GetPlataforms();
    GameSceneDto GetGameScene();
    ~MapEditor() = default;

    void Print();
};
#endif

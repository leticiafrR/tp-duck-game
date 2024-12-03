#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "data/gameScene.h"
#include "editor/constantsEditor.h"
#include "multimedia/ThemeInfo.h"

#include "constants.h"

using std::optional;
using std::set;
using std::string;
using std::unordered_map;
using std::vector;
class MapEditor {
private:
    YAML::Node config;
    int platformsCounter;
    string fileName;
    string filePath;

public:
    MapEditor();
    explicit MapEditor(const string& fileName);

    void AddFileName(const string& fileName);
    void AddAPlataform(const float& x, const float& y, const float& w, const float& h,
                       const vector<string>& edges);
    void SaveChanges();
    void AddPlayerSpawnPoint(const float& x, const float& y);
    void AddCollectableSpawnPoint(const float& x, const float& y);
    void AddBoxSpawnPoint(const float& x, const float& y);
    void AddTheme(const string& theme);
    void AddFullMapSize(const size_t& x, const size_t& y);
    void DeleteALevel();
    void ModificateAPlataform(const string& plataformName, const float& x, const float& y,
                              const float& w, const float& h, const vector<string>& edges);
    void DeleteAPlatform(const string& plataformName);
    optional<GroundDto> TakePltaform(const Vector2D pos);
    vector<GroundDto> GetPlatforms();
    GameSceneDto GetGameScene();
    unordered_map<BoxID_t, Vector2D> GetBoxes();
    ~MapEditor() = default;
};
#endif

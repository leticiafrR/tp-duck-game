#ifndef THEMEINFO_H
#define THEMEINFO_H
#include <string>

#include <yaml-cpp/yaml.h>
using std::string;
class ThemeInfo {
private:
    YAML::Node config;

public:
    ThemeInfo();
    string GetBackgroundPath(const string& name);
    string GetTilePath(const string& name);
    string GetTileDataPath(const string& name);
};
#endif

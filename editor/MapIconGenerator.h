#ifndef MAP_ICON_GENERATOR_H
#define MAP_ICON_GENERATOR_H
#include <QIcon>
#include <unordered_map>
#include "yaml-cpp/yaml.h"

class MapIconGenerator {

public:
    MapIconGenerator();
    QIcon getIcon(std::string &name);
    std::vector<std::string> getIconsNames();
    std::vector<std::string> getTypes();
    std::list<std::string> getIconsNames(std::string &type);
    ~MapIconGenerator();

private:
    std::string type;
    void setIcons();
    void setIcons(std::string &type);
    std::unordered_map<std::string, QIcon> icons;
    YAML::Node data;
};

#endif // MAP_ICON_GENERATOR_H

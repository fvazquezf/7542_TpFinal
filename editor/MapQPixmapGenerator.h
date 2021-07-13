#ifndef MAP_QPIXMAP_GENERATOR_H
#define MAP_QPIXMAP_GENERATOR_H
#include <QIcon>
#include <QPixmap>
#include <unordered_map>
#include "yaml-cpp/yaml.h"
#include "constantes.h"

class MapQPixmapGenerator {

public:
    MapQPixmapGenerator();
    QPixmap getPixmap(std::string &name);
    std::vector<std::string> getPixmapsNames();
    std::vector<std::string> getTypes();
    std::list<std::string> getPixmapsNames(std::string &type);
    ~MapQPixmapGenerator();

private:
    std::string type;
    void setPixmaps();
    void setPixmaps(std::string &type);
    std::unordered_map<std::string, QPixmap> pixmaps;
    YAML::Node data;
};

#endif // MAP_QPIXMAP_GENERATOR_H

#include "MapIconGenerator.h"
#include "paths.h"
#include <QDebug>

MapIconGenerator::MapIconGenerator() {
    data = YAML::LoadFile(MAP_ICON_CONFIG_PATH);
    this->setIcons();
}
std::vector<std::string> MapIconGenerator::getTypes() {
    return data["types"].as<std::vector<std::string>>();
}

std::list<std::string> MapIconGenerator::getIconsNames(std::string &type) {
    std::vector<std::vector<std::string>> iconsData;
    iconsData = data[type].as<std::vector<std::vector<std::string>>>();

    std::list<std::string> res;
    unsigned long n = iconsData.size();
    for(unsigned long i = 0; i < n; i++) {
        res.push_back(iconsData[i][0]);
    }
    return res;
}


void MapIconGenerator::setIcons() {
    std::vector<std::string> types = this->getTypes();
    for(unsigned long i = 0; i < types.size(); i++) {
        this->setIcons(types[i]);
    }
}

void MapIconGenerator::setIcons(std::string &type) {
    std::vector<std::vector<std::string>> iconsData;
    iconsData = data[type].as<std::vector<std::vector<std::string>>>();
    for(unsigned long i = 0; i < iconsData.size(); i++) {
        QIcon icon(QString::fromStdString(iconsData[i][1]));
        icons[iconsData[i][0]] = icon;
    }
}


QIcon MapIconGenerator::getIcon(std::string &name) {
    if(icons.find(name) == icons.end()){
        return QIcon();
    }
    return icons[name];
}

std::vector<std::string> MapIconGenerator::getIconsNames() {
    std::vector<std::string> keys;
    keys.reserve(icons.size());

    for(auto kv : icons) {
        keys.push_back(kv.first);
    }
    return  keys;
}

MapIconGenerator::~MapIconGenerator() {

}

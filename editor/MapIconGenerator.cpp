#include "MapIconGenerator.h"
#define MAP_ICON_CONFIG_PATH "mapIconsType.yml"
#include <QDebug>
MapIconGenerator::MapIconGenerator() {
    data = YAML::LoadFile(MAP_ICON_CONFIG_PATH);
    this->setIcons();
}

void MapIconGenerator::setIcons() {
    std::vector<std::string> types = data["types"].as<std::vector<std::string>>();
    for(unsigned long i = 0; i < types.size(); i++) {
        qDebug() <<  "TYPE: " << QString::fromStdString(types[i]);
        this->setIcons(types[i]);
    }
}

void MapIconGenerator::setIcons(std::string &type) {
    std::vector<std::vector<std::string>> iconsData;
    iconsData = data[type].as<std::vector<std::vector<std::string>>>();
    for(unsigned long i = 0; i < iconsData.size(); i++) {
        qDebug() <<  "ICON: " << QString::fromStdString(iconsData[i][0]);
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

#include "MapQPixmapGenerator.h"

MapQPixmapGenerator::MapQPixmapGenerator() {
    data = YAML::LoadFile(MAP_ICON_CONFIG_PATH);
    this->setPixmaps();
}
std::vector<std::string> MapQPixmapGenerator::getTypes() {
    return data["types"].as<std::vector<std::string>>();
}

std::list<std::string> MapQPixmapGenerator::getPixmapsNames(std::string &type) {
    std::vector<std::vector<std::string>> pixmapsData;
    pixmapsData = data[type].as<std::vector<std::vector<std::string>>>();

    std::list<std::string> res;
    unsigned long n = pixmapsData.size();
    for(unsigned long i = 0; i < n; i++) {
        res.push_back(pixmapsData[i][0]);
    }
    return res;
}


void MapQPixmapGenerator::setPixmaps() {
    std::vector<std::string> types = this->getTypes();
    for(unsigned long i = 0; i < types.size(); i++) {
        this->setPixmaps(types[i]);
    }
}

void MapQPixmapGenerator::setPixmaps(std::string &type) {
    std::vector<std::vector<std::string>> pixmapsData;
    pixmapsData = data[type].as<std::vector<std::vector<std::string>>>();
    for(unsigned long i = 0; i < pixmapsData.size(); i++) {
        QIcon icon(QString::fromStdString(pixmapsData[i][1]));
        pixmaps[pixmapsData[i][0]] = icon.pixmap(QSize(32, 32));
    }
}


QPixmap MapQPixmapGenerator::getPixmap(std::string &name) {
    if(pixmaps.find(name) == pixmaps.end()) {
        return QPixmap();
    }
    return pixmaps[name];
}


std::vector<std::string> MapQPixmapGenerator::getPixmapsNames() {
    std::vector<std::string> keys;
    keys.reserve(pixmaps.size());

    for(auto kv : pixmaps) {
        keys.push_back(kv.first);
    }
    return  keys;
}

MapQPixmapGenerator::~MapQPixmapGenerator() {

}

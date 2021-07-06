//
// Created by leogm99 on 5/7/21.
//

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <iostream>
#include "MapView.h"
#include "Camera.h"

MapView::MapView(SdlWindow& window,
                 const std::string &mapInfoFile)
: window(window),
  columns(0),
  rows(0){
    try {
        mapInformation = YAML::LoadFile(mapInfoFile);
    } catch (const std::exception& e){
        // si no puedo cargar la config
        // tengo que abortar la carga
        // me desconecto
        // handlear;
    }
}

void MapView::loadMap(const std::string &mapFile) {
    try {
        map = YAML::Load(mapFile);
    } catch (const std::exception& e){
        // si no puede cargar el mapa
        // rip, nos desconectamos
        // handlear
    }

    columns = map["size_columns"].as<size_t>();
    rows = map["size_rows"].as<size_t>();
    loadBackground();
    loadWalls();
    loadZones();
    //loadDroppedWeapons();
}

void MapView::loadBackground() {
    std::string background = map["background"].as<std::string>();
    std::string backgroundPath;
    auto backgrounds = mapInformation["background"].as<std::vector<std::vector<std::string>>>();
    for (auto& it : backgrounds){
        if (it[0] == background){
            backgroundPath = it[1];
            break;
        }
    }

    if (backgroundPath.empty()){
        // tirar excepcion
    }

    // use move semantics
    textureHolder.emplace(std::piecewise_construct,
                          std::forward_as_tuple("background"),
                          std::forward_as_tuple(backgroundPath, window));
    // reference to loaded texture
    auto& backgroundTexture = textureHolder.at("background");

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            backgroundTiles.emplace_back(backgroundTexture, 32, 32, i, j);
}

void MapView::loadWalls() {
    auto wallInformation = mapInformation["walls"].as<std::vector<std::vector<std::string>>>();
    for (auto& wall : wallInformation){
        if (map[wall[0]]){ // si hay informacion sobre esa pared, creo y guardo la textura
            auto wallPositions = map[wall[0]].as<std::vector<std::pair<int, int>>>();
            textureHolder.emplace(std::piecewise_construct,
                                  std::forward_as_tuple(wall[0]),
                                  std::forward_as_tuple(wall[1], window));
            auto& wallTexture = textureHolder.at(wall[0]);
            for (auto& wallPosition : wallPositions) { // para ese tipo de pared, obtengo las posiciones
                walls.emplace_back(wallTexture,
                                   32,
                                   32,
                                   wallPosition.first,
                                   wallPosition.second);
            }
        }
    }
}


void MapView::loadZones() {
    auto zoneInformation = mapInformation["zones"].as<std::vector<std::vector<std::string>>>();
    for (auto& zone : zoneInformation) {
        if (map[zone[0]]) { // si hay informacion sobre esa zona, creo y guardo la textura
            auto zonePositions = map[zone[0]].as<std::vector<std::pair<int, int>>>();
            textureHolder.emplace(std::piecewise_construct,
                                  std::forward_as_tuple(zone[0]),
                                  std::forward_as_tuple(zone[1], window));
            auto &zoneTexture = textureHolder.at(zone[0]);
            for (auto &zonePosition : zonePositions) { // para ese tipo de pared, obtengo las posiciones
                walls.emplace_back(zoneTexture,
                                   32,
                                   32,
                                   zonePosition.first,
                                   zonePosition.second);
            }
        }
    }
}

MapView::~MapView() {

}

void MapView::render(Camera &cam) {
    for (auto& tile : backgroundTiles){
        cam.render(tile, 0);
    }

    for (auto& wall : walls){
        cam.render(wall, 0);
    }

    for (auto& weapon : droppedWeapons){
        weapon.draw(cam);
    }
}

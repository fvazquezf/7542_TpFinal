//
// Created by leogm99 on 5/7/21.
//

#ifndef MAPVIEW_H
#define MAPVIEW_H


#include <vector>
#include "weapons/DroppedWeapon.h"
#include "NonMovable.h"
#include "yaml-cpp/yaml.h"
class MapView {
private:
    // funciones para cargar las texturas
    void loadBackground();
    void loadWalls();
    void loadZones();
    void loadWeapons();

    SdlWindow& window;
    std::vector<NonMovable> backgroundTiles;
    std::vector<NonMovable> walls;
    std::vector<NonMovable> zones;
    std::vector<DroppedWeapon> droppedWeapons;
    std::map<std::string, SdlTexture> textureHolder;

    YAML::Node mapInformation;
    YAML::Node map;
    size_t columns;
    size_t rows;
public:
    MapView(SdlWindow& window,
            const std::string& mapInfoFile);

    MapView(const MapView& other) = delete;
    MapView& operator=(const MapView& other) = delete;

    void loadMap(const std::string& mapFile);
    void render(Camera& cam);

    MapView(MapView&& other) noexcept;
    MapView& operator=(MapView&& other) noexcept;

    ~MapView();

};


#endif

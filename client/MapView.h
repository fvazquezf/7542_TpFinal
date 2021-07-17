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

    SdlWindow& window;
    std::vector<NonMovable> backgroundTiles;
    std::vector<NonMovable> walls;
    std::vector<NonMovable> zones;
    std::vector<DroppedWeapon> droppedWeapons;
    std::map<std::string, SdlTexture> textureHolder;

    YAML::Node& clientConfig;
    YAML::Node map;
    size_t columns;
    size_t rows;
public:
    MapView(SdlWindow& window,
            YAML::Node& clientConfig);

    MapView(const MapView& other) = delete;
    MapView& operator=(const MapView& other) = delete;

    void loadMap(const std::string& mapFile);
    void render(Camera& cam);

    MapView(MapView&& other) ;
    MapView& operator=(MapView&& other) ;

    ~MapView();

};


#endif

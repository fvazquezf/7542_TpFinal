#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <vector>
#include <mutex>
#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include "anim/Terrorist.h"

class WorldView {
private:
    SdlWindow& window;

    SdlTexture terror;
    // entre las texturas estara el player (capaz es una textura aparte)
    // en realidad deberia ser un vector de cosas renderizables
    // tales que todas tengan el metodo render etc etc
    std::vector<Terrorist> textures;

    // varios hilos acceden de manera concurrente a la view
    // SDL, Drawer, Receiver
    // funciona como monitor

    std::mutex worldMutex;
    // Player player; -> lo podemos controlar, es distinto al resto
    // GameMap map; -> algo asi?
public:
    explicit WorldView(SdlWindow& window);

    WorldView(const WorldView& other) = delete;
    WorldView& operator=(const WorldView& other) = delete;

    WorldView(WorldView&& other) = delete;
    WorldView& operator=(WorldView&& other) = delete;

    void createTerrorist();

    void update();
    void render();

    ~WorldView();
};


#endif

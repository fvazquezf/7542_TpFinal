#include <QApplication>
#include "MapConfigWindow.h"
#include "IntroWindow.h"
#include "constantes.h"

int main(int argc, char* argv[]) {
    
    QApplication app(argc, argv);

    MapConfigWindow* window = new MapConfigWindow(nullptr);
    window->open();
    window->close();
    IntroWindow introWindow(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    introWindow.run();
    window->show();

    return app.exec();
}

#include <QApplication>
#include "MapConfigWindow.h"
#include "IntroWindow.h"


#define WIDTH 1024
#define HEIGHT 720 

int main(int argc, char* argv[]){
    
    QApplication app(argc, argv);

    MapConfigWindow* window = new MapConfigWindow(nullptr);
    window->open();
    window->close();
    IntroWindow introWindow(window, WIDTH, HEIGHT);
    introWindow.run();
    window->show();

    return app.exec();
}

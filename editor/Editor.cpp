//#include "./Editor.h"
#include <QApplication>
#include "mainwindow.h"

/*Editor::Editor() {
}

Editor::~Editor() {
}*/

//int Editor::run(int argc, const char *argv[]) {
int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle("Counter Strike 2D");
    w.show();

    return app.exec();
}

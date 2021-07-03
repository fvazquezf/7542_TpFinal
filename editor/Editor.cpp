#include "./Editor.h"
#include <QApplication>
#include "mainwindow.h"

Editor::Editor() {
}

Editor::~Editor() {
}

int Editor::run(int argc, const char *argv) {
    QApplication app(argc, nullptr);
    MainWindow w;
    w.setWindowTitle("Counter Strike 2D");
    w.show();

    return app.exec();
}

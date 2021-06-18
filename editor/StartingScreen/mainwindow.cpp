#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./MapEditor.h"
#include "./MapCreationWindow.h"
#include <QString>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Q_INIT_RESOURCE(resource);
    QFontDatabase::addApplicationFont(":/fonts/counter_strike.ttf");
    QFont CounterStrikeFont("Counter-Strike", 12, QFont::Normal);
    this->setFont(CounterStrikeFont);
    this->setWindowTitle("Counter Strike 2D");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createButton_clicked()
{
    QString mapName = "nombre mapa";
    QString mapSize = "mmm";
    this->execCreationWindow(mapName, mapSize);
}

void MainWindow::on_editButton_clicked()
{
    QString mapName = "nombre mapa";
    this->execEditorWindow(mapName);
}

void MainWindow::execCreationWindow(QString &mapName, QString &mapSize) {
    this->close();
    MapCreationWindow mapCreationWindow;
    mapCreationWindow.setWindowTitle("Counter Strike 2D - Map editor");
    mapCreationWindow.exec();
    this->show();
}

void MainWindow::execEditorWindow(QString &mapName) {
    this->close();
    MapEditor mapEditor;
    mapEditor.setWindowTitle("Counter Strike 2D - Map editor");
    mapEditor.setLayout(mapEditor.getLayout());
    mapEditor.exec();
    this->show();
}

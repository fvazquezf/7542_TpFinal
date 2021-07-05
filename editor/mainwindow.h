#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MapConfigWindow.h"
#include <QVBoxLayout>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleStartPushButton();

private:
    void setStart();

};
#endif // MAINWINDOW_H

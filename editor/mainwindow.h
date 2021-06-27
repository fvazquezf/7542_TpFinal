#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MapConfigWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
    Ui::MainWindow *ui;
    void setStart();

};
#endif // MAINWINDOW_H

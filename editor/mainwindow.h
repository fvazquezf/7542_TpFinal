#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CounterStrikeStyle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createButton_clicked();

    void on_editButton_clicked();

private:
    Ui::MainWindow *ui;
    CounterStrikeStyle styler;
    void execCreationWindow();
    void execEditorWindow(QString &mapName);
};
#endif // MAINWINDOW_H

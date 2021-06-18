#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void execCreationWindow(QString &mapName, QString &mapSize);
    void execEditorWindow(QString &mapName);
};
#endif // MAINWINDOW_H

#ifndef MAPCONFIGWINDOW_H
#define MAPCONFIGWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QPushButton>

#include "./CounterStrikeStyle.h"
#include "./QEditorMapListWidget.h"
#include "./LogInInfo.h"

namespace Ui {
class MapConfigWindow;
}

class MapConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MapConfigWindow(QWidget *parent, int width, int height, LogInInfo &info);
    ~MapConfigWindow();

private slots:
    void handleJoinPushButton();
    void handleClickMouse(QListWidgetItem * item);

private:
    int width;
    int height;
    LogInInfo& info;
    CounterStrikeStyle styler;
    QVBoxLayout* mainLayout;
    QHBoxLayout* bottonLayout;
    QEditorMapListWidget* qEditorMapList;

    QString selectedMap;

    void execCreationWindow();
    void execEditorWindow(QString &mapName);
    void setMainLayout();
    void setBottonLayout();

};

#endif // MAPCONFIGWINDOW_H

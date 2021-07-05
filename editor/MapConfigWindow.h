#ifndef MAPCONFIGWINDOW_H
#define MAPCONFIGWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>

#include "./CounterStrikeStyle.h"
#include "./MapEditor.h"
#include "./MapCreationWindow.h"
#include "./QEditorMapListWidget.h"

class MapConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MapConfigWindow(QWidget *parent = nullptr);
    ~MapConfigWindow();

private slots:
    void handleEditPushButton();
    void handleCreatePushButton();
    void handleJoinPushButton();
    void handleClickMouse(QListWidgetItem * item);

private:
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

#ifndef QEDITOR_MAP_LIST_H
#define QEDITOR_MAP_LIST_H
#include <QListWidget>
#include <QListWidgetItem>
#include <QDir>
#include "LogInInfo.h"
#define DIRECTORY_PATH "../maps"

class QEditorMapListWidget : public QListWidget {
    Q_OBJECT

public:
    QEditorMapListWidget(QWidget *parent, int width, int height, LogInInfo &info);
    void update();
private:
    void setMapItems();
    void setMapItem(QString &mapName);
    LogInInfo& info;


};

#endif   //QEDITOR_MAP_LIST_H

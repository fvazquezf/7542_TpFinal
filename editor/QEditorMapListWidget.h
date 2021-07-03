#ifndef QEDITOR_MAP_LIST_H
#define QEDITOR_MAP_LIST_H
#include <QListWidget>
#include <QListWidgetItem>
#include <QDir>
#define DIRECTORY_PATH "../maps"

class QEditorMapListWidget : public QListWidget {
    Q_OBJECT

public:
    QEditorMapListWidget(QWidget* parent);
    void update();
private:
    void setMapItems();
    void setMapItem(QString &mapName);


};

#endif   //QEDITOR_MAP_LIST_H

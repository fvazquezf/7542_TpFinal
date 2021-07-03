#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <map>
#include "yaml-cpp/yaml.h"

namespace Ui {
class MapWidget;
}

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    MapWidget(QWidget *parent = nullptr, std::string file_name = "");
    ~MapWidget();

private:
    Ui::MapWidget *ui;

    YAML::Node img_config;
    int height;
    int width;
    std::map<std::pair<int, int>,std::string> items_map;
    std::string file_name;
    void setValues();
    void setWidgets();

};

#endif // MAPWIDGET_H

#ifndef MAPLISTWINDOW_H
#define MAPLISTWINDOW_H

#include <QDialog>
#include <QWidget>
#include "CounterStrikeStyle.h"
namespace Ui {
class MapListWindow;
}

class MapListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MapListWindow(QWidget *parent = nullptr);
    ~MapListWindow();

private:
    Ui::MapListWindow *ui;
    CounterStrikeStyle styler;
};

#endif // MAPLISTWINDOW_H

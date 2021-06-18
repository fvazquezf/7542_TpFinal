#ifndef MAPLISTWINDOW_H
#define MAPLISTWINDOW_H

#include <QDialog>
#include <QWidget>

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
};

#endif // MAPLISTWINDOW_H

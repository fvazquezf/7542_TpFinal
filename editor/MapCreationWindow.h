#ifndef MAPCREATIONWINDOW_H
#define MAPCREATIONWINDOW_H

#include <QDialog>
#include "./CounterStrikeStyle.h"

namespace Ui {
class MapCreationWindow;
}

class MapCreationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MapCreationWindow(QWidget *parent = nullptr);
    ~MapCreationWindow();

private slots:

    void on_continueButton_clicked();
    void on_backButton_clicked();

private:
    Ui::MapCreationWindow *ui;
    CounterStrikeStyle styler;
    QString mapName;
    QString mapSize;
};

#endif // MAPCREATIONWINDOW_H

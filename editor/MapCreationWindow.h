#ifndef MAPCREATIONWINDOW_H
#define MAPCREATIONWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <utility>
#include "MapEditor.h"
#include "CounterStrikeStyle.h"
#include "constantes.h"
class MapCreationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MapCreationWindow(QWidget *parent = nullptr);
    ~MapCreationWindow();

private slots:
    void on_saveButton_clicked();

private:
    CounterStrikeStyle styler;
    QString mapName;
    QString mapSize;
    QVBoxLayout* mainLayout;
    QLineEdit* mapNameEditLine;
    QComboBox* sizeComboBox;
    QPushButton* saveButton;
    std::pair<int,int> getSize();

    void setUpSizeField();
    void setUpMapNameField();
    void setUpSaveButton();
    void setUpTitle();
    void setUpAll();
};

#endif // MAPCREATIONWINDOW_H

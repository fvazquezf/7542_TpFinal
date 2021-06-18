#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QDialog>
#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QListView>
#include <QStringListModel>
namespace Ui {
class MapEditor;
}

class MapEditor : public QDialog
{
    Q_OBJECT

public:
    explicit MapEditor(QWidget *parent = nullptr);
    QGridLayout* getLayout();
    ~MapEditor();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MapEditor *ui;
    QListView* map;
    QListView* items;
};

#endif // MAPEDITOR_H

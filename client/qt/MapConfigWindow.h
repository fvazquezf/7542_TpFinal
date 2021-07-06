#ifndef MAPCONFIGWINDOW_H
#define MAPCONFIGWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QPushButton>
#include <QLineEdit>

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
    explicit MapConfigWindow(QWidget *parent, int width, int height, LogInInfo &info, bool create);
    ~MapConfigWindow() override;

private slots:
    void handleJoinPushButton();
    void handleClickMouse(QListWidgetItem * item);

private:
    int width;
    int height;
    LogInInfo& info;
    bool createWindow;
    CounterStrikeStyle styler;
    QVBoxLayout* mainLayout;
    QHBoxLayout* bottonLayout;
    QLineEdit* usernameLineEdit;
    QEditorMapListWidget* qEditorMapList;

    QString selectedMap;

    void execCreationWindow();
    void setMainLayout();
    void setBottonLayout();
    void setEditLinesLayout();

};

#endif // MAPCONFIGWINDOW_H

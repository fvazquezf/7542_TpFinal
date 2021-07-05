#ifndef USERNAMEWINDOW_H
#define USERNAMEWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include "./CounterStrikeStyle.h"
#include "./MapConfigWindow.h"
#include "./LogInInfo.h"

namespace Ui {
class UserNameWindow;
}

class UserNameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserNameWindow(QWidget *parent, int width, int height, LogInInfo &info);
    ~UserNameWindow();

private slots:
    void on_saveButton_clicked();

private:
    int width;
    int height;
    LogInInfo* info;
    QVBoxLayout* mainLayout;
    CounterStrikeStyle styler;
    QLineEdit* usernameLineEdit;
    QPushButton* saveButton;
    void setUpAll();
    void setMainTitle();
    void setButtonsLayout();
    void setEditLinesLayout();
};

#endif // USERNAMEWINDOW_H

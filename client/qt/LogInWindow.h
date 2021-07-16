#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "CounterStrikeStyle.h"
#include <QMessageBox>

#include "LogInInfo.h"
#include "IntroWindow.h"
#include "UserNameWindow.h"

class LogInWindow : public QDialog
{
    Q_OBJECT

public:
    LogInWindow(QWidget *parent, int width, int height, LogInInfo &info);
    ~LogInWindow() override;

private slots:
    void on_saveButton_clicked();

private:
    int width;
    int height;
    LogInInfo& info;
    QVBoxLayout* mainLayout;
    CounterStrikeStyle styler;
    QLineEdit* ipLineEdit;
    QLineEdit* portLineEdit;
    QPushButton* saveButton;
    UserNameWindow* userNameWindow;
    void setUpAll();
    void setMainTitle();
    void setButtonsLayout();
    void setEditLinesLayout();
    void playIntro();
};
#endif // LOGINWINDOW_H

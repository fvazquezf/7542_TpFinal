#include "LogInWindow.h"
#include <QDebug>
LogInWindow::LogInWindow(QWidget *parent, int width, int height, LogInInfo &info)
    : QDialog(parent), width(width), height(height), info(info), userNameWindow(nullptr)
{
    this->setWindowTitle("Counter Strike 2D");
    this->setFixedHeight(height);
    this->setFixedWidth(width);
    styler.setCounterStrikeFont(this, 16);
    this->open();
    this->playIntro();
    setUpAll();
}

void LogInWindow::playIntro() {
    this->open();
    this->close();
    IntroWindow introWindow(this, width, height);
    introWindow.run();
}

LogInWindow::~LogInWindow()
{
}

void LogInWindow::setUpAll() {
    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    this->setMainTitle();
    this->setEditLinesLayout();
    this->setButtonsLayout();
}

void LogInWindow::setMainTitle() {
    QLabel* titleLabel = new QLabel();
    titleLabel->setText("Cofiguration");
    mainLayout->addWidget(titleLabel);
}


void LogInWindow::setEditLinesLayout() {

    QHBoxLayout* ipLayout = new QHBoxLayout();
    QHBoxLayout* portLayout = new QHBoxLayout();

    QLabel* ipLabel = new QLabel();
    QLabel* portLabel = new QLabel();
    ipLabel->setText("IP");
    portLabel->setText("PORT");

    ipLineEdit = new QLineEdit();
    portLineEdit = new QLineEdit();

    ipLayout->addWidget(ipLabel);
    portLayout->addWidget(portLabel);

    ipLayout->addWidget(ipLineEdit);
    portLayout->addWidget(portLineEdit);

    mainLayout->addLayout(ipLayout);
    mainLayout->addLayout(portLayout);
}

void LogInWindow::setButtonsLayout() {
    QVBoxLayout* buttonsLayout = new QVBoxLayout();

    saveButton = new QPushButton();
    saveButton->setText("continue");
    buttonsLayout->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));
    mainLayout->addLayout(buttonsLayout);
}

void LogInWindow::on_saveButton_clicked()
{
    std::string ip = this->ipLineEdit->text().toStdString();
    std::string port = this->portLineEdit->text().toStdString();
    if(ip == "") {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr("IP field is empty."),
                             QMessageBox::Close);
        return;
    }
    if(port == "") {
        QMessageBox::warning(this, tr("Configuration error"),
                             tr("PORT field is empty."),
                             QMessageBox::Close);
        return;
    }
    try {
        info.socket.connect(ip.c_str(), port.c_str());
    } catch (const std::exception& e){
        QMessageBox::warning(this, tr("Configuration error"),
                             tr("Error trying to connect to server."),
                             QMessageBox::Close);
        return;
    }

    userNameWindow = new UserNameWindow(this, width, height, info);
    this->close();
    userNameWindow->show();
}

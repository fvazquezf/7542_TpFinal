#include "UserNameWindow.h"

UserNameWindow::UserNameWindow(QWidget *parent, int width, int height, LogInInfo &info)
    : QDialog(parent), width(width), height(height), info(&info)
{
    this->setWindowTitle("Counter Strike 2D");
    styler.setCounterStrikeFont(this, 16);
    setUpAll();

}

UserNameWindow::~UserNameWindow()
{
}

void UserNameWindow::setUpAll() {

    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    this->setMainTitle();
    this->setEditLinesLayout();
    this->setButtonsLayout();
}

void UserNameWindow::setMainTitle() {
    QLabel* titleLabel = new QLabel();
    titleLabel->setText("Log In");
    mainLayout->addWidget(titleLabel);
}


void UserNameWindow::setEditLinesLayout() {

    QHBoxLayout* usernameLayout = new QHBoxLayout();

    QLabel* userLabel = new QLabel();
    userLabel->setText("USERNAME");

    usernameLineEdit = new QLineEdit();

    usernameLayout->addWidget(userLabel);

    usernameLayout->addWidget(usernameLineEdit);

    mainLayout->addLayout(usernameLayout);
}

void UserNameWindow::setButtonsLayout() {
    QVBoxLayout* buttonsLayout = new QVBoxLayout();

    saveButton = new QPushButton();
    saveButton->setText("continue");
    buttonsLayout->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));
    mainLayout->addLayout(buttonsLayout);
}

void UserNameWindow::on_saveButton_clicked()
{
    std::string username = this->usernameLineEdit->text().toStdString();
    if(username == "") {
        QMessageBox::warning(this, tr("Log In error"),
                             tr("Username field is empty."),
                             QMessageBox::Close);
        return;
    }

    info->username = username;

    MapConfigWindow* mapWindow = new MapConfigWindow(nullptr, width, height, *info);
    this->close();
    mapWindow->show();
}



#include <client/commands/Command.h>
#include <memory>
#include <client/commands/ListGame.h>
#include <client/commands/ListMaps.h>
#include "UserNameWindow.h"

UserNameWindow::UserNameWindow(QWidget *parent, int width, int height, LogInInfo &info)
    : QDialog(parent),
    width(width),
    height(height),
    info(info),
    createGame("Crear una partida"),
    joinGame("Unirse a una partida existente")
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
    this->setButtonsLayout();
}

void UserNameWindow::setMainTitle() {
    QLabel* titleLabel = new QLabel();
    titleLabel->setText("Log In");
    mainLayout->addWidget(titleLabel);
}

void UserNameWindow::setButtonsLayout() {
    QVBoxLayout* vLayout = new QVBoxLayout();
    mainLayout->addLayout(vLayout);
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(&createGame);
    buttonsLayout->addWidget(&joinGame);
    connect(&createGame, SIGNAL(clicked()), this, SLOT(on_createButton_clicked()));
    connect(&joinGame, SIGNAL(clicked()), this, SLOT(on_joinButton_clicked()));
    mainLayout->addLayout(buttonsLayout);
}

void UserNameWindow::on_createButton_clicked()
{
    Protocol prot;
    std::unique_ptr<Command> listMaps = std::unique_ptr<Command>(new ListMaps());
    std::function<void(std::vector<unsigned char>)> sender =
            std::bind(&UserNameWindow::send, this, std::placeholders::_1);
    listMaps->serialize(sender, prot);

    MapConfigWindow* mapWindow = new MapConfigWindow(nullptr, width, height, info, true);
    this->close();
    mapWindow->show();
}

void UserNameWindow::on_joinButton_clicked() {
    Protocol prot;
    std::unique_ptr<Command> listGames = std::unique_ptr<Command>(new ListGame());
    std::function<void(std::vector<unsigned char>)> sender =
            std::bind(&UserNameWindow::send, this, std::placeholders::_1);
    listGames->serialize(sender, prot);

    MapConfigWindow* mapWindow = new MapConfigWindow(nullptr, width, height, info, false);
    this->close();
    mapWindow->show();
}

// callback para send desde qt!
void UserNameWindow::send(std::vector<unsigned char> msg) {
    info.socket.send(reinterpret_cast<const char *>(msg.data()), msg.size());
}

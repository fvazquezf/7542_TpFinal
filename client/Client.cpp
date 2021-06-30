#include <sstream>
#include "Client.h"
#include "WorldView.h"
#include "SdlLoop.h"
#include "Drawer.h"


Client::Client()
: window(800, 600, false, "unaVentana"){
}

void Client::launch(const char *host, const char *serv) {
    // TODO: aca va todo lo de qt supongo
    // de alguna manera tiene que conseguir host y el puerto
    // se van a poder enviar los mensajes de crear y unirse
    // despues se debe resolver el login
    // el login termina cuando se recibe el mensaje de update de mapa
    // ahi empieza a renderizar y comienza la partida
    // los botones de qt deben despachar en 2 comandos
    // create y join
    
    // Desde aca hasta el proximo comentario, esta seccion es temporal, hasta que tengamos qt
    std::string s;
    do {
        std::cout << "Crea o unite a una partida escribiendo Crear <nombre> o Unirse <nombre>\n";
        std::getline(std::cin, s);
        std::cout << s;
    }
    while (s.find("Unirse") == std::string::npos && s.find("Crear" ) == std::string::npos);

    std::stringstream stream(s);
    std::string comando;
    std::string nombre;
}
    // End seccion
}

Client::Client(Client &&other) noexcept
: clientSocket(std::move(other.clientSocket)),
  window(800, 600, false, "unaVentana"){
}

Client &Client::operator=(Client &&other) noexcept {
    if (this == &other){
        return *this;
    }

    clientSocket = std::move(other.clientSocket);
    return *this;
}

void Client::login(std::stringstream &stream) {
    stream >> comando;
    stream >> nombre;
    if (comando == "Crear"){
        comms.push(std::unique_ptr<Command>(new CreateGame(nombre)));
    } else {
        comms.push(std::unique_ptr<Command>(new JoinGame(nombre)));
    }

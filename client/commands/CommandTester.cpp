#include "Command.h"
#include "CreateGame.h"
#include "JoinGame.h"
#include "ListGame.h"
#include "Move.h"
#include <arpa/inet.h>
#include <memory>

// test pavo para ver si funca el protocolo
void callback(std::vector<unsigned char> msg){
    switch (msg.at(0)){
        case LIST:
            puts("Message: list");
            puts("First Expected: 0x6c");
            break;
        case CREATE :{
            puts("Message: create");
            puts("First Expected: 0x6e");
            uint16_t msgLen = ntohs((msg.at(1) << 8) | msg.at(2));
            printf("Game name received length: %d\n", msgLen);
            break;
        }
        case JOIN :{
            puts("Message: join");
            puts("First Expected: 0x6a");
            uint16_t msgLen = ntohs((msg.at(1) << 8) | msg.at(2));
            printf("Game name received length: %d\n", msgLen);
            break;
        }
        case MOVE: {
            puts("Message: move");
            switch(msg.at(1)){
                case Move::Direction::UP:
                    puts("Direction: UP");
                    break;
                case Move::Direction::DOWN:
                    puts("Direction: DOWN");
                    break;
                case Move::Direction::LEFT:
                    puts("Direction: LEFT");
                    break;
                case Move::Direction::RIGHT:
                    puts("Direction: RIGHT");
                    break;
            }
            break;
        }
        case STOP_MOVE: {
            puts("Message: stop move");
            switch(msg.at(1)){
                case Move::Direction::UP:
                    puts("Direction: UP");
                    break;
                case Move::Direction::DOWN:
                    puts("Direction: DOWN");
                    break;
                case Move::Direction::LEFT:
                    puts("Direction: LEFT");
                    break;
                case Move::Direction::RIGHT:
                    puts("Direction: RIGHT");
                    break;
            }
            break;
        }
    }
    for (unsigned char & it : msg){
        printf("%02x ", it);
    }
    puts("");
}


int main(){
    std::string game = "Hola, una partidusqui";
    /*auto create = std::unique_ptr<Command>(new CreateGame(game));
    auto join = std::unique_ptr<Command>(new JoinGame(game));
    auto list = std::unique_ptr<Command>(new ListGame());
    auto move = std::unique_ptr<Command>(new Move(Move::UP));
    auto move2 = std::unique_ptr<Command>(new Move(Move::DOWN));
    auto move3 = std::unique_ptr<Command>(new Move(Move::LEFT));
    auto move4 = std::unique_ptr<Command>(new Move(Move::RIGHT));
    auto movestop = std::unique_ptr<Command>(new Move(Move::UP, true));
    auto move2stop = std::unique_ptr<Command>(new Move(Move::DOWN, true));
    auto move3stop = std::unique_ptr<Command>(new Move(Move::LEFT, true));
    auto move4stop = std::unique_ptr<Command>(new Move(Move::RIGHT, true));*/

    Protocol prot;
    std::function<void(std::vector<unsigned char>)> f = &callback;
    /*create->serialize(f, prot);
    join->serialize(f, prot);
    list->serialize(f, prot);
    move->serialize(f, prot);
    move2->serialize(f, prot);
    move3->serialize(f, prot);
    move4->serialize(f, prot);
    movestop->serialize(f, prot);
    move2stop->serialize(f, prot);
    move3stop->serialize(f, prot);
    move4stop->serialize(f, prot);*/

    std::vector<unsigned char> unFloat;
    prot.serializePosition(unFloat, 3.455413413f);
    for (auto& it : unFloat){
        printf("%d ", it);
    }
    puts("");
    // float 0.4
    float respuesta = prot.deserializePosition(unFloat);
    printf("Ultimo float: %f\n", respuesta);
}
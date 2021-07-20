#include "Command.h"
#include "CreateGame.h"
#include "JoinGame.h"
#include "ListGame.h"
#include "Move.h"
#include "Rotate.h"
#include <arpa/inet.h>
#include <memory>

// test pavo para ver si funca el protocolo
void callback(std::vector<unsigned char> msg) {
    switch (msg.at(0)) {
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
            switch(msg.at(1)) {
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
            switch(msg.at(1)) {
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
        case ROTATE: {
            break;
        }
        case SCORE_UPDATE:{
            break;
        }
    }
    for (unsigned char & it : msg) {
        printf("%x ", it);
    }
    puts("");
}


int main() {
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
    std::map<uint8_t, std::pair<float, float>> m {
            {1, {1.234f, 3.678f}},
            {2, {2.314f, 34.231f}}
    };

    std::function<void(std::vector<unsigned char>)> f = &callback;
    auto rotate = std::unique_ptr<Command>(new Rotate(153));
    rotate->serialize(f, prot);
    //prot.updatePositions(m, f);

    //std::vector<unsigned char> positions = {1, 0x00, 0x00, 0x04, 0xd2, 0x00, 0x00, 0x0e, 0x5e,
    //                                        2, 0x00, 0x00, 0x09, 0x0a, 0x00, 0x00, 0x85, 0xb7};
    //auto m2 = prot.deserializePositions(positions);
    //for (auto& it : m2) {
    //    printf("%d %f %f", it.first, it.second.first, it.second.second);
    //}
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

    /*std::vector<unsigned char> unFloat;
    prot.serializePosition(unFloat, 3.455413413f);
    for (auto& it : unFloat) {
        printf("%d ", it);
    }
    puts("");
    // float 0.4
    float respuesta = prot.deserializePosition(unFloat);
    printf("Ultimo float: %f\n", respuesta);*/
    printf("SCORE UPDATE TESTER:\n");
    std::vector<std::tuple<uint8_t , uint8_t, uint8_t, uint16_t, bool>> scores;
    scores.emplace_back(std::make_tuple(1, 20, 10, 10000, 0));
    scores.emplace_back(std::make_tuple(2, 10, 5, 1500, 1));
    prot.updateScore(scores, f);
    std::vector<unsigned char> scoresSerialized{
        0x1, 0x14, 0xa, 0x10, 0x27, 0x0, 0x2, 0xa, 0x5, 0xdc, 0x5, 0x1
    };
    // se esperaria que me devuelva 2 tuplas
    // su contenido siendo (1, 20, 10, 10000, 0) y (2, 10, 5, 1500, 1)
    auto scoresBack = prot.deserializeScores(scoresSerialized);
    for (auto& score : scoresBack) {
        printf("SCORE: %u %u %u %u %u\n",
               std::get<0>(score),
               std::get<1>(score),
               std::get<2>(score),
               std::get<3>(score),
               std::get<4>(score));
    }
    // pasa la prueba de fuego (cppunit 0 | commandTester 1)
}
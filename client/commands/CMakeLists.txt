project(sdl-demo)

add_library(commands
        Command.cpp
        CreateGame.cpp
        JoinGame.cpp
        ListGame.cpp
        Move.cpp
        CommandTester.cpp Rotate.cpp Rotate.h Attack.cpp Attack.h)
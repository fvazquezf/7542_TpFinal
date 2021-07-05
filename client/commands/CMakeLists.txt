project(sdl-demo)

add_library(commands
        Command.cpp
        CreateGame.cpp
        JoinGame.cpp
        ListGame.cpp
        Move.cpp
        Rotate.cpp Rotate.h Attack.cpp Attack.h ChangeWeapon.cpp ChangeWeapon.h Buy.cpp Buy.h Pickup.cpp Pickup.h Reload.cpp Reload.h)
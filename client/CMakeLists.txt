project(sdl-demo)

add_library(sdlloop
        SdlLoop.cpp
        Sender.cpp
        WorldView.cpp
        Camera.cpp
        Receiver.cpp
        Receiver.h
        Stencil.cpp
        Stencil.h
        Button.cpp
        Button.h
        BuyingMenu.cpp
        BuyingMenu.h
        Drawer.cpp
        Drawer.h
        Client.cpp
        Hud.cpp
        Renderizable.cpp
        NonMovable.cpp
        SoundManager.cpp
        MapView.cpp
        LobbyScreen.cpp
        Cursor.cpp SkinSelector.cpp SkinSelector.h CharacterManager.cpp CharacterManager.h)

add_subdirectory(sdlwrap)
add_subdirectory(anim)
add_subdirectory(commands)
add_subdirectory(weapons)
add_subdirectory(qt)

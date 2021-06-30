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
        Client.cpp)

add_subdirectory(sdlwrap)
add_subdirectory(anim)
add_subdirectory(commands)
add_subdirectory(weapons)

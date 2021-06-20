project(sdl-demo)


add_library(sdlloop
        SdlLoop.cpp
        Sender.cpp
        WorldView.cpp
        Camera.cpp Receiver.cpp Receiver.h)

add_subdirectory(sdlwrap)
add_subdirectory(anim)
add_subdirectory(commands)

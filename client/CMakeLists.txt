project(sdl-demo)


add_library(sdlloop
        SdlLoop.cpp)

add_subdirectory(sdlwrap)
add_subdirectory(anim)
add_subdirectory(commands)


project(sdl-demo)

FILE(GLOB sdlwrapper "*.cpp")

add_library(sdlwrapperclasses ${sdlwrapper})

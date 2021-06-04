cmake_minimum_required(VERSION 3.16)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -DDEBUG -Wall -Werror -fno-inline -pedantic -pedantic-errors -O3 -pthread")

project(sld-demo)

add_executable(sdl_demo ./main.cpp)
add_subdirectory(sdlwrap)
add_subdirectory(anim)

target_link_libraries(sdl_demo anim sdlwrapperclasses SDL2 SDL2_image)

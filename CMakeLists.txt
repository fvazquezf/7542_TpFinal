cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -DDEBUG -Wall -fno-inline -pedantic -pedantic-errors -O3 -pthread")

project(sdl-demo)

add_subdirectory(client)
add_subdirectory(libs/box2d)
add_subdirectory(common)

add_executable(client_main ./client/main.cpp)
add_executable(box2d_demo HelloWorld.cpp)
add_executable(demo_movimiento ./client/demo_movimiento.cpp)
add_executable(commandTester ./client/commands/CommandTester.cpp)


target_link_libraries(client_main anim sdlwrapperclasses SDL2 SDL2_image sdlloop common commands )
target_link_libraries(box2d_demo box2d anim sdlwrapperclasses SDL2 SDL2_image)
target_link_libraries(demo_movimiento box2d anim sdlwrapperclasses SDL2 SDL2_image)
target_link_libraries(commandTester common commands)

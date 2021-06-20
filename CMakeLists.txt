cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -DDEBUG -Wall -fno-inline -pedantic -pedantic-errors -pthread")

project(sdl-demo)

add_subdirectory(libs/box2d)
add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)

# Ejecutables demo_movimiento
add_executable(client_main ./client/main.cpp)
add_executable(box2d_demo HelloWorld.cpp)
#add_executable(demo_movimiento demo_movimiento.cpp)
add_executable(commandTester ./client/commands/CommandTester.cpp)

# Ejecutables esqueleto cliente-servidor
add_executable(esqueleto_server ./server/main.cpp)

# Linkage demo_movimiento
target_link_libraries(client_main sdlloop anim sdlwrapperclasses SDL2 SDL2_image common lib_common commands)
target_link_libraries(box2d_demo box2d anim sdlwrapperclasses SDL2 SDL2_image)
#target_link_libraries(demo_movimiento lib_server box2d anim sdlwrapperclasses SDL2 SDL2_image )
target_link_libraries(commandTester common commands)

# Linkage esqueleto cliente-servidor
target_link_libraries(esqueleto_server lib_server lib_common common box2d anim sdlwrapperclasses SDL2 SDL2_image)



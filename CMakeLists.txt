cmake_minimum_required(VERSION 3.10)

# para fanalyzer, updatear a gcc 11 -> va a tirar warnings de possible null argument cuando se llame a new
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -DDEBUG -Wall -fno-inline -pedantic -pedantic-errors -pthread")

project(sdl-demo)

#**************************************
#***********Including QT***************
#**************************************
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets)
find_package(Qt5 COMPONENTS REQUIRED Widgets Core Multimedia MultimediaWidgets)
qt5_wrap_ui(ui_wrap ${EDITORUI})
qt5_wrap_cpp(moc_sources ${EDITOR_HEADERS})
qt5_add_resources(QT_RESOURCES ./client/qt/resources.qrc)

##*************************************
#***********Including yaml*************
#**************************************
find_package(yaml-cpp REQUIRED)

#**************************************
#*******Including subdirectories*******
#**************************************
add_subdirectory(libs/box2d)
add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(editor)

#**************************************
#********Creating excecutables*********
#**************************************

file(GLOB CLIENT_QT_SRC
     "./client/qt/*.cpp"
     "./client/qt/*.h"
     "./client/qt/*.ui"
)

file(GLOB EDITOR_QT_SRC
     "./editor/*.cpp"
     "./editor/*.h"
     "./editor/*.ui"
)

#**************************************
#******** Creating excecutables********
#**************************************

# Ejecutables cliente
add_executable(cs2d ./client/main.cpp ${CLIENT_QT_SRC})
#add_executable(editor ./editor/Editor.cpp)
#add_executable(box2d_demo HelloWorld.cpp)
#add_executable(demo_movimiento demo_movimiento.cpp)
#add_executable(commandTester ./client/commands/CommandTester.cpp)

# Ejecutables esqueleto cliente-servidor
add_executable(cs2d_server ./server/main.cpp)

# Ejecutables editor
add_executable(cs2d_editor ${EDITOR_QT_SRC})

#**************************************
#**********Linking libraries***********
#**************************************

# Linkage client
target_link_libraries(cs2d Qt5::Widgets Qt5::Core Qt5::Multimedia Qt5::MultimediaWidgets sdlloop sdlwrapperclasses anim SDL2 SDL2_image SDL2_mixer lib_common commands weapons SDL2_gfx yaml-cpp SDL2_ttf)

# Linkage esqueleto cliente-servidor
target_link_libraries(cs2d_server lib_server lib_common box2d yaml-cpp)

# Linkage editor
target_link_libraries(cs2d_editor Qt5::Multimedia Qt5::MultimediaWidgets Qt5::Widgets Qt5::Core Qt5::Gui yaml-cpp)

#**************************************
#***************Install****************
#**************************************

set(BIN "/usr/bin")
set(RESOURCES "/var/cs2d")


install(TARGETS cs2d DESTINATION ${BIN} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

install(TARGETS cs2d_server DESTINATION ${BIN} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

install(TARGETS cs2d_editor DESTINATION ${BIN} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/sprites DESTINATION ${RESOURCES})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/maps DESTINATION ${RESOURCES})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/client/qt/resources DESTINATION ${RESOURCES})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/config DESTINATION ${RESOURCES})


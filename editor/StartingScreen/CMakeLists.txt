cmake_minimum_required(VERSION 3.5)

project(StartingScreen LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

qt5_add_resources(RC_SRC resource.qrc)

add_executable(StartingScreen
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    MapListWindow.cpp MapListWindow.h MapListWindow.ui
    MapCreationWindow.cpp MapCreationWindow.h MapCreationWindow.ui
    MapEditor.cpp MapEditor.h MapEditor.ui
    MapWidget.cpp MapWidget.h MapWidget.ui
    PiecesList.cpp PiecesList.h
    PuzzleWidget.cpp PuzzleWidget.h
    ${RC_SRC}
)

target_link_libraries(StartingScreen PRIVATE Qt5::Widgets Qt5::Core yaml-cpp)

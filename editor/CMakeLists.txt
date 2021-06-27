cmake_minimum_required(VERSION 3.5)

project(editor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

qt5_add_resources(RC_SRC resource.qrc)

add_executable(editor
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    MapListWindow.cpp MapListWindow.h MapListWindow.ui
    MapCreationWindow.cpp MapCreationWindow.h MapCreationWindow.ui
    MapEditor.cpp MapEditor.h MapEditor.ui
    PiecesList.cpp PiecesList.h
    CounterStrikeStyle.cpp CounterStrikeStyle.h
    QTile.cpp QTile.h
    QEditorMapWidget.cpp QEditorMapWidget.h
    MapIconGenerator.cpp MapIconGenerator.h
    QEditorItemsWidget.cpp QEditorItemsWidget.h
    ${RC_SRC}
)

target_link_libraries(editor PRIVATE Qt5::Widgets Qt5::Core yaml-cpp)

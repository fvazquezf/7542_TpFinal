cmake_minimum_required(VERSION 3.5)
project(editor)

find_package(Qt5Widgets) 
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets) 
qt5_wrap_ui(ui_wrap ${EDITORUI}) 
qt5_wrap_cpp(moc_sources ${EDITOR_HEADERS}) 

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt5_add_resources(RC_SRC resource.qrc)

add_executable(editor
    mainwindow.cpp mainwindow.h mainwindow.ui
    Editor.cpp
    MapListWindow.cpp MapListWindow.h MapListWindow.ui
    MapCreationWindow.cpp MapCreationWindow.h MapCreationWindow.ui
    MapEditor.cpp MapEditor.h MapEditor.ui
    PiecesList.cpp PiecesList.h
    CounterStrikeStyle.cpp CounterStrikeStyle.h
    QTile.cpp QTile.h
    QEditorMapWidget.cpp QEditorMapWidget.h
    MapIconGenerator.cpp MapIconGenerator.h
    QEditorItemsWidget.cpp QEditorItemsWidget.h
    QEditorMapListWidget.cpp QEditorMapListWidget.h
    MapConfigWindow.cpp MapConfigWindow.h MapConfigWindow.ui
    ${RC_SRC}
)

target_link_libraries(editor Qt5::Widgets Qt5::Core Qt5::Gui yaml-cpp)

cmake_minimum_required(VERSION 3.5)

qt5_add_resources(QT_RESOURCES resources.qrc)

add_library(startingScreen
    main.cpp
    LogInWindow.cpp LogInWindow.h
    IntroWindow.cpp IntroWindow.h
    MapConfigWindow.cpp MapConfigWindow.h MapConfigWindow.ui
    QEditorMapListWidget.cpp QEditorMapListWidget.h
    CounterStrikeStyle.cpp CounterStrikeStyle.h
    UserNameWindow.cpp UserNameWindow.h UserNameWindow.ui
    LogInInfo.cpp LogInInfo.h
    ${QT_RESOURCES}
)
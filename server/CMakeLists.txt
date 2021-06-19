add_library(lib_server
    match.cpp
    main.cpp
    server.cpp
    th_acceptor.cpp
    th_login.cpp
    th_sender.cpp
    user.cpp
    GamesMonitor.cpp
    ThReceiver.cpp
    PlayerModel.cpp
    WorldModel.cpp
    updates/Update.cpp
    events/ClientEvent.cpp
    events/ClientEvent.h
    Broadcaster.cpp
    events/MoveEvent.cpp updates/PositionUpdate.cpp updates/PositionUpdate.h)
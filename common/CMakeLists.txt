project(sdl-demo)
add_library(lib_common
            socket.cpp
            Thread.cpp
            ProtectedQueue.h
            BlockingQueue.h
            Protocol.cpp ConfigVariables.h Exception.cpp Exception.h)

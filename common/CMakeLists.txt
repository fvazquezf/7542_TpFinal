project(sdl-demo)
add_library(lib_common
  lock.cpp
  #protocol.cpp
  socket.cpp
  thread.cpp
  thread.cpp
)

add_library(common
        Protocol.cpp
        Thread.cpp
        BlockingQueue.h)

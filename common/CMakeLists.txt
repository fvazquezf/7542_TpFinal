project(sdl-demo)
add_library(lib_common
  lock.cpp
  protocol.cpp
  socket.cpp
  thread.cpp
  ta_te_ti_cifrador.cpp
  ta_te_ti_constantes.h
  ta_te_ti_descifrador.cpp
  thread.cpp
)

add_library(common
        Protocol.cpp
        Thread.cpp
        BlockingQueue.h)

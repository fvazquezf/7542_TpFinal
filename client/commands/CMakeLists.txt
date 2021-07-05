project(sdl-demo)

add_library(commands
        Command.cpp
        CreateGame.cpp
        JoinGame.cpp
        ListGame.cpp
        Move.cpp
        Rotate.cpp 
	Attack.cpp 
	ChangeWeapon.cpp 
	Buy.cpp 
	Pickup.cpp 
	Reload.cpp 
	Plant.cpp 
	ListMaps.cpp)

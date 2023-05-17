cmake_minimum_required(VERSION 3.24)
project(Proyecto_II_Datos_II)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5.1 COMPONENTS graphics audio)


add_executable(Proyecto_II_Datos_II
        main.cpp
        Game/PacMan4.h
        Game/PacMan4.cpp
        Player/player.h
        Player/player.cpp
        Player/lives.h
        Player/lives.cpp
        Resorces/block.h
        Resorces/block.cpp
        Resorces/points.h
        Resorces/points.cpp
        ghosts/ghosts.h
        ghosts/ghosts.cpp
        Game/PacMan2.h
        Game/PacMan2.cpp
        Resorces/power.h
        Resorces/power.cpp
        Game/PacMan.h
        Game/PacMan.cpp
        Game/PacMan3.h
        Game/PacMan3.cpp
        Resorces/puntuacion_final.h
        Resorces/puntuacion_final.cpp
        Server/Server.h
        Pathfinding/Pathdinging_A_Star.cpp
        Pathfinding/Pathdinging_A_Star.h)

target_link_libraries(Proyecto_II_Datos_II sfml-graphics sfml-audio sfml-system sfml-window)

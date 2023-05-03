cmake_minimum_required(VERSION 3.24)
project(Proyecto_II_Datos_II)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5.1 COMPONENTS graphics audio)


add_executable(Proyecto_II_Datos_II
        main.cpp
        Game/PacMan.h
        Game/PacMan.cpp
        Player/player.h
        Player/player.cpp
        Player/lives.h
        Player/lives.cpp
        block.h
        block.cpp
        points.h points.cpp ghosts/ghosts.h ghosts/ghosts.cpp)

target_link_libraries(Proyecto_II_Datos_II sfml-graphics sfml-audio sfml-system)

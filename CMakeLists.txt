cmake_minimum_required(VERSION 3.7)
project(rogue)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        include/inventory.h
        include/item.h
        include/map.h
        include/monster.h
        include/player.h
        include/util.h
        src/inventory.c
        src/item.c
        src/main.c
        src/map.c
        src/monster.c
        src/player.c
        src/util.c)

add_executable(rogue ${SOURCE_FILES})
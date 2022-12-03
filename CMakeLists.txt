cmake_minimum_required(VERSION 3.24)
project(pacman)

set(APP_NAME pacman)
set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES    Map/map.h
                    Input/input.h
                    Input/colours.h
                    Graphics/graphics.h
                    AI/ai.h
                    Physics/physics.h
                    GameObject/game_object.h
                    GameLogic/game_logic.h
                    Utils/utils.h)

set(SOURCE_FILES    main.c
                    Map/map.c
                    Input/input.c
        Input/colours.c
                    Graphics/graphics.c
                    AI/ai.c
                    Physics/physics.c
                    GameObject/game_object.c
                    GameLogic/game_logic.c
                    Utils/utils.c)

add_executable(${APP_NAME} ${SOURCE_FILES})

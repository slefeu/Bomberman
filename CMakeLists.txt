cmake_minimum_required(VERSION 3.17)
project(bomberman)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(raylib 4.0.0 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

if (UNIX)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
endif()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif ()

# Ajouter ici les .cpp
set(INDIE_SRC
    src/main.cpp
    src/Engine/Tools/Cameraman.cpp
    src/Engine/Tools/Timer.cpp
    src/Engine/Core/Core.cpp
    src/Engine/Core/Collision.cpp
    src/Entities/Player.cpp
    src/Entities/Box.cpp
    src/Entities/Bomb.cpp
    src/Entities/Explosion.cpp
    src/Scenes/Game.cpp
    src/Scenes/Home.cpp)
    
add_executable(${PROJECT_NAME} ${INDIE_SRC})
if (UNIX)
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Werror)
endif ()
target_link_libraries(${PROJECT_NAME} raylib)
    
# Ajouter ici les dossiers contenants les .hpp
target_include_directories(${PROJECT_NAME} PRIVATE include/Engine/Tools)
target_include_directories(${PROJECT_NAME} PRIVATE include/Engine/Core)
target_include_directories(${PROJECT_NAME} PRIVATE include/Scenes)
target_include_directories(${PROJECT_NAME} PRIVATE include/Entities)
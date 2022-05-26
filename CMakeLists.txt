cmake_minimum_required(VERSION 3.17)
project(bomberman)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(raylib 4.0.0 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

if(UNIX)
  set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

if (WIN32)
  file(COPY assets/ DESTINATION assets/)
endif()

# Ajouter ici les .cpp
set(
  INDIE_SRC
  src/main.cpp

  src/Tools/Timer.cpp
  src/Tools/Round.cpp

  src/Engine/Cameraman.cpp
  src/Engine/Core.cpp
  src/Engine/Collision.cpp
  src/Engine/GameData.cpp

  src/Components/Render3D.cpp
  src/Components/BoxCollider.cpp
  src/Components/Transform3D.cpp
  src/Components/Render.cpp

  src/Prefabs/Player.cpp
  src/Prefabs/Box.cpp
  src/Prefabs/Bomb.cpp
  src/Prefabs/Crate.cpp
  src/Prefabs/Explosion.cpp
  src/Prefabs/Wall.cpp
  src/Prefabs/Fire.cpp
  src/Prefabs/Item.cpp

  src/Scenes/Game.cpp
  src/Scenes/Home.cpp
)

add_executable(${PROJECT_NAME} ${INDIE_SRC})
if(UNIX)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Werror)
endif()
target_link_libraries(${PROJECT_NAME} raylib)

# Ajouter ici les dossiers contenants les .hpp
target_include_directories(${PROJECT_NAME} PRIVATE include/Components)
target_include_directories(${PROJECT_NAME} PRIVATE include/Engine)
target_include_directories(${PROJECT_NAME} PRIVATE include/Prefabs)
target_include_directories(${PROJECT_NAME} PRIVATE include/Scenes)
target_include_directories(${PROJECT_NAME} PRIVATE include/Tools)

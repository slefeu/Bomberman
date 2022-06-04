cmake_minimum_required(VERSION 3.17)
project(bomberman)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(OpenGL_GL_PREFERENCE GLVND)
set(CMAKE_CXX_STANDARD 20)

if(UNIX)
  find_program(TIDY "clang-tidy")
    if(TIDY)
      set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
    endif()
endif()

find_package(raylib 4.0.0 REQUIRED)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

file(COPY assets/ DESTINATION assets/)

# Ajouter ici les .cpp
set(
  INDIE_SRC
  src/main.cpp

  src/Engine/Tools/Timer.cpp
  src/Engine/Tools/Round.cpp
  src/Engine/Tools/Error.cpp

  src/Engine/Core/Cameraman.cpp
  src/Engine/Core/Core.cpp
  src/Engine/Core/Collision.cpp
  src/Engine/Core/GameData.cpp
  src/Engine/Core/Model3D.cpp
  src/Engine/Core/Entity.cpp

  src/Engine/Components/BoxCollider.cpp
  src/Engine/Components/Transform3D.cpp
  src/Engine/Components/Render.cpp

  src/Indie/Prefabs/Player.cpp
  src/Indie/Prefabs/Bomb.cpp
  src/Indie/Prefabs/Crate.cpp
  src/Indie/Prefabs/Wall.cpp
  src/Indie/Prefabs/Fire.cpp
  src/Indie/Prefabs/Item.cpp

  src/Indie/Scenes/Game.cpp
  src/Indie/Scenes/Home.cpp

  src/Indie/UI/Button.cpp

  src/Engine/Lib/Mouse.cpp
  src/Engine/Lib/Font.cpp
  src/Engine/Lib/Text.cpp
  src/Engine/Lib/Music.cpp
  src/Engine/Lib/Sound.cpp
)

add_executable(${PROJECT_NAME} ${INDIE_SRC})

target_link_libraries(${PROJECT_NAME} raylib)

# Ajouter ici les dossiers contenants les .hpp
target_include_directories(${PROJECT_NAME} PRIVATE include/Engine/Components)
target_include_directories(${PROJECT_NAME} PRIVATE include/Engine/Core)
target_include_directories(${PROJECT_NAME} PRIVATE include/Engine/Tools)
target_include_directories(${PROJECT_NAME} PRIVATE include/Engine/Lib)
target_include_directories(${PROJECT_NAME} PRIVATE include/Indie/Prefabs)
target_include_directories(${PROJECT_NAME} PRIVATE include/Indie/Scenes)
target_include_directories(${PROJECT_NAME} PRIVATE include/Indie/UI)
target_include_directories(${PROJECT_NAME} PRIVATE include/Indie)

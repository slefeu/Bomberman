cmake_minimum_required(VERSION 3.17)
project(bomberman)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(OpenGL_GL_PREFERENCE GLVND)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

set(CMAKE_MODULE_LINKER_FLAGS "fsanitize=address")
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
  src/Engine/ECS/Entity.cpp
  src/Engine/ECS/Components/BoxCollider.cpp
  src/Engine/ECS/Components/Transform3D.cpp
  src/Engine/ECS/Components/Render.cpp

  src/Indie/GameCore/Core.cpp
  src/Indie/GameCore/GameData.cpp

  src/Indie/Prefabs/Player.cpp
  src/Indie/Prefabs/Bomb.cpp
  src/Indie/Prefabs/Crate.cpp
  src/Indie/Prefabs/Wall.cpp
  src/Indie/Prefabs/Fire.cpp
  src/Indie/Prefabs/Item.cpp

  src/Indie/Scenes/Game.cpp
  src/Indie/Scenes/Home.cpp
  src/Indie/Scenes/PlayerSelect.cpp

  src/Indie/UI/Button.cpp

  src/Lib/Mouse.cpp
  src/Lib/Text.cpp
  src/Lib/Music.cpp
  src/Lib/Sound.cpp
  src/Lib/AudioDevice.cpp
  src/Lib/Sprite.cpp
  src/Lib/Color.cpp
  src/Lib/Window.cpp
  src/Lib/Fps.cpp
  src/Lib/Rectangle.cpp
  src/Lib/Controller.cpp
  src/Lib/Model3D.cpp
  src/Lib/Cameraman.cpp

)

add_executable(${PROJECT_NAME} ${INDIE_SRC})

target_link_libraries(${PROJECT_NAME} raylib)
# target_link_libraries(${PROJECT_NAME} raylib_encapsulation)

# Ajouter ici les dossiers contenants les .hpp
target_include_directories(${PROJECT_NAME} PRIVATE include/Engine/ECS/Components)
target_include_directories(${PROJECT_NAME} PRIVATE include/Engine/ECS)
target_include_directories(${PROJECT_NAME} PRIVATE include/Engine/Tools)
target_include_directories(${PROJECT_NAME} PRIVATE include/Engine)
target_include_directories(${PROJECT_NAME} PRIVATE include/Indie/Scenes)
target_include_directories(${PROJECT_NAME} PRIVATE include/Indie/Prefabs)
target_include_directories(${PROJECT_NAME} PRIVATE include/Indie/UI)
target_include_directories(${PROJECT_NAME} PRIVATE include/Indie/GameCore)

# à enlever quand ça sera compilé en lib statique
target_include_directories(${PROJECT_NAME} PRIVATE include/Lib)

target_compile_options(${PROJECT_NAME} PUBLIC ${CXX_FLAGS})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

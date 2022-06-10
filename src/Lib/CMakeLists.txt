# add_library(
#     raylib_encapsulation
#     STATIC
#     Mouse.cpp
#     Text.cpp
#     Music.cpp
#     Sound.cpp
#     AudioDevice.cpp
#     Sprite.cpp
#     Color.cpp
#     Window.cpp
#     Fps.cpp
#     Rectangle.cpp
#     Controller.cpp
#     Model3D.cpp
#     Cameraman.cpp
# )
# set_property(TARGET raylib_encapsulation PROPERTY CXX_STANDARD 20)
# set_property(TARGET raylib_encapsulation PROPERTY POSITION_INDEPENDENT_CODE ON)

# target_include_directories(raylib_encapsulation PUBLIC
# ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(raylib_encapsulation raylib)
cmake_minimum_required(VERSION 3.10)
project(raylib_test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(raylib QUIET)

add_executable(raylib_test src/main.cpp
        src/include/Ball.cpp
        src/include/Ball.h
        src/include/Paddle.cpp
        src/include/Paddle.h
        src/include/Game.cpp
        src/include/Game.h
        src/include/Block.cpp
        src/include/Block.h
        src/include/Physics.cpp
        src/include/Physics.h)

if(raylib_FOUND)
    target_link_libraries(raylib_test PRIVATE raylib)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(RAYLIB REQUIRED raylib)
    target_include_directories(raylib_test PRIVATE ${RAYLIB_INCLUDE_DIRS})
    target_link_libraries(raylib_test PRIVATE ${RAYLIB_LIBRARIES})
endif()
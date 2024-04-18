cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BESKAR_EDITOR ON)

project(pacman)

add_subdirectory(beskar)
add_executable(pacman)
target_sources(pacman PRIVATE src/main.cpp) # no need to add headers here, only sources are required

if (DEFINED BESKAR_EDITOR)
    target_link_libraries(pacman PRIVATE beskar_editor)
else ()
    target_link_libraries(pacman PRIVATE beskar_engine)
endif ()
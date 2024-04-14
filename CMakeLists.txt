cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(pacman)

add_compile_definitions(BESKAR_EDITOR)

add_subdirectory(beskar)
add_executable(pacman)
target_sources(pacman PRIVATE src/main.cpp) # no need to add headers here, only sources are required
target_link_libraries(pacman PRIVATE beskar_engine)
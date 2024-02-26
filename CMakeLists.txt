cmake_minimum_required(VERSION 3.2)

project(pacman)

# DEPENDENCIES DIRECTORIES
set(DEPS_ROOT_DIR "${CMAKE_SOURCE_DIR}/deps")
set(DEPS_INCLUDE_DIR "${DEPS_ROOT_DIR}/include")
set(DEPS_LIBRARIES_DIR "${DEPS_ROOT_DIR}/lib/")

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(pacman ${INCLUDE_DIR}/mesh.h ${INCLUDE_DIR}/shader.h main.cpp src/mesh.cpp src/shader.cpp)

target_include_directories(pacman PUBLIC $<BUILD_INTERFACE:${INCLUDE_DIR}>)

target_include_directories(pacman PUBLIC ${DEPS_INCLUDE_DIR})
target_link_directories(pacman PUBLIC ${DEPS_LIBRARIES_DIR})

target_link_libraries(pacman glfw GLEW "-framework Cocoa" "-framework OpenGL" "-framework IOKit")
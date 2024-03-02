cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(pacman)

# DEPENDENCIES DIRECTORIES
set(DEPS_ROOT_DIR "${CMAKE_SOURCE_DIR}/deps")
set(DEPS_INCLUDE_DIR "${DEPS_ROOT_DIR}/include")
set(DEPS_LIBRARIES_DIR "${DEPS_ROOT_DIR}/lib/")
####

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(pacman src/gl_texture.cpp src/gl_renderer.cpp src/gl_shader.cpp src/gl_mesh.cpp main.cpp)

target_include_directories(pacman PUBLIC BUILD_INTERFACE<${CMAKE_CURRENT_SOURCE_DIR}/src/include>)

target_include_directories(pacman PUBLIC ${DEPS_INCLUDE_DIR})
target_link_directories(pacman PUBLIC ${DEPS_LIBRARIES_DIR})

if(WIN32)
    target_compile_definitions(pacman PRIVATE GLEW_STATIC)
    target_link_libraries(pacman glfw3 glew32s opengl32)
elseif(APPLE)
    target_link_libraries(pacman glfw.3.4 GLEW "-framework Cocoa"  "-framework OpenGL" "-framework IOKit")
elseif(UNIX)
    message("https://cmake.org/cmake/help/latest/variable/UNIX.html?highlight=unix")
endif()
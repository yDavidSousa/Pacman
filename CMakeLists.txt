cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(pacman)

# DEPENDENCIES DIRECTORIES
set(DEPS_ROOT_DIR "${CMAKE_SOURCE_DIR}/deps")
set(DEPS_INCLUDE_DIR "${DEPS_ROOT_DIR}/include")
set(DEPS_LIBRARIES_DIR "${DEPS_ROOT_DIR}/lib/")

set(IMGUI_SRC
        src/imgui/imgui_impl_opengl3.h
        src/imgui/imgui_impl_opengl3.cpp
        src/imgui/imgui_impl_opengl3_loader.h
        src/imgui/imgui_impl_glfw.h
        src/imgui/imgui_impl_glfw.cpp
        src/imgui/imgui.h
        src/imgui/imgui.cpp
        src/imgui/imgui_draw.cpp
        src/imgui/imgui_tables.cpp
        src/imgui/imgui_widgets.cpp
        src/imgui/imgui_demo.cpp
)

add_executable(pacman
    ${IMGUI_SRC}
    src/mesh_asset.cpp
    src/sprite_asset.cpp
    src/gl_texture.cpp
    src/gl_renderer.cpp
    src/gl_shader.cpp
    src/gl_mesh.cpp
    main.cpp
)

target_include_directories(pacman 
    PUBLIC BUILD_INTERFACE<${CMAKE_CURRENT_SOURCE_DIR}/src/include> 
    PRIVATE BUILD_INTERFACE<${CMAKE_CURRENT_SOURCE_DIR}/src>
)

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
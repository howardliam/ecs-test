cmake_minimum_required(VERSION 3.5.0)

cmake_policy(SET CMP0072 NEW)

set(PROJ_NAME ecs-test)

project(${PROJ_NAME} VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

add_executable(${PROJ_NAME}
    src/glad/gl.h
    src/glad/gl.c
    src/main.cpp
    src/window.hpp
    src/window.cpp
    src/shader.hpp
    src/shader.cpp
    src/utils.hpp

    src/imgui/imconfig.h
    src/imgui/imgui.cpp
    src/imgui/imgui.h
    src/imgui/imgui_demo.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_internal.h
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imstb_rectpack.h
    src/imgui/imstb_textedit.h
    src/imgui/imstb_truetype.h
    src/imgui/imgui_impl_opengl3.cpp
    src/imgui/imgui_impl_opengl3.h
    src/imgui/imgui_impl_opengl3_loader.h
    src/imgui/imgui_impl_sdl2.cpp
    src/imgui/imgui_impl_sdl2.h
)

set(LIBS pthread SDL2 OpenGL glm)
target_link_libraries(${PROJ_NAME} ${LIBS})

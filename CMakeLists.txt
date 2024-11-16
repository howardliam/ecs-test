cmake_minimum_required(VERSION 3.5.0)

cmake_policy(SET CMP0072 NEW)

set(PROJ_NAME ecs-test)

project(${PROJ_NAME} VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

set(PROJ_SRC
    src/main.cpp
    src/window.hpp
    src/window.cpp
    src/shader.hpp
    src/shader.cpp
    src/model.hpp
    src/model.cpp
    src/texture.hpp
    src/texture.cpp
    src/framebuffer.hpp
    src/framebuffer.cpp
)

set(GLAD_SRC
    src/glad/gl.h
    src/glad/gl.c
)

set(IMGUI_SRC
    src/imgui/imconfig.h
    src/imgui/imgui.cpp
    src/imgui/imgui.h
    src/imgui/imgui_demo.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_internal.h
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_impl_opengl3.cpp
    src/imgui/imgui_impl_opengl3.h
    src/imgui/imgui_impl_opengl3_loader.h
    src/imgui/imgui_impl_sdl3.cpp
    src/imgui/imgui_impl_sdl3.h
    src/imgui/imstb_rectpack.h
    src/imgui/imstb_textedit.h
    src/imgui/imstb_truetype.h

    src/imgui/implot.cpp
    src/imgui/implot.h
    src/imgui/implot_demo.cpp
    src/imgui/implot_internal.h
    src/imgui/implot_items.cpp
)

set(STB_SRC
    src/stb/stb_image.c
    src/stb/stb_image.h
)

add_executable(${PROJ_NAME}
    ${PROJ_SRC}
    ${GLAD_SRC}
    ${IMGUI_SRC}
    ${STB_SRC}
)

set(LIBS pthread SDL3::SDL3 OpenGL glm)
target_link_libraries(${PROJ_NAME} ${LIBS})

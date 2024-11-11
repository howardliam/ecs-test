cmake_minimum_required(VERSION 3.5.0)

cmake_policy(SET CMP0072 NEW)

set(PROJ_NAME ecs-test)

project(${PROJ_NAME} VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

add_executable(${PROJ_NAME}
    src/gl.h
    src/gl.c
    src/main.cpp
    src/window.hpp
    src/window.cpp
    src/shader.hpp
    src/shader.cpp
    src/utils.hpp
)

set(LIBS pthread SDL2 OpenGL glm)
target_link_libraries(${PROJ_NAME} ${LIBS})

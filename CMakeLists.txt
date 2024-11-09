cmake_minimum_required(VERSION 3.5.0)

set(PROJ_NAME ecs-test)

project(${PROJ_NAME} VERSION 0.1.0 LANGUAGES C CXX)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

add_executable(${PROJ_NAME}
    src/main.cpp
    src/window.hpp
    src/window.cpp
    src/shader.hpp
    src/shader.cpp
)

set(LIBS pthread glfw GLEW OpenGL glm)
target_link_libraries(${PROJ_NAME} ${LIBS})

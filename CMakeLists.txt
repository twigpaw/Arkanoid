cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME Arkanoid)
project(${PROJECT_NAME})

add_subdirectory(lib/glad)
include_directories(lib/glad/include)

add_subdirectory(lib/glfw)
include_directories(lib/glfw/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(${PROJECT_NAME} src/main.cpp src/Context.cpp src/Program.cpp src/Utils.cpp)
target_link_libraries(${PROJECT_NAME} glfw glad)
  
cmake_minimum_required(VERSION 3.29.1)
project(MyFirstTriangle)

set(CMAKE_CXX_STANDARD 17)  # for c++17

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(MyFirstTriangle ${SOURCE_FILES} "src/glad.c")
include_directories(include)

add_subdirectory(glfw-3.4)
include_directories(glfw-3.4/include)

source_group(TREE "${CMAKE_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

target_link_libraries(MyFirstTriangle glfw ${GLFW_LIBRARIES})

cmake_minimum_required(VERSION 3.2)
project(OPENGL)

set(CMAKE_CXX_STANDARD 17)

file(GLOB shaders src/shaders/*.shader)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(HEADERS include/glad/glad.h include/KHR/khrplatform.h include/shader.h)
set(SOURCE src/shader.cpp)
#add_executable(OPENGL ${HEADERS} src/draw_triangle.cpp src/glad.c)
#add_executable(OPENGL ${HEADERS} src/draw_rectangle_EBO.cpp src/glad.c)
#add_executable(OPENGL ${HEADERS} src/exercise1.cpp src/glad.c)
#add_executable(OPENGL ${HEADERS} src/exercise2.cpp src/glad.c)
#add_executable(OPENGL ${HEADERS} src/exercise3.cpp src/glad.c)
add_executable(OPENGL ${HEADERS} ${SOURCE} ${shaders} src/shaders.cpp src/glad.c)
target_link_libraries(OPENGL ${CONAN_LIBS})
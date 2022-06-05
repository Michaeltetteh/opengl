cmake_minimum_required(VERSION 3.2)
project(OPENGL)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


add_executable(OPENGL main.cpp)
target_link_libraries(OPENGL ${CONAN_LIBS})
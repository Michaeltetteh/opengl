cmake_minimum_required(VERSION 3.0)
project(OPENGL)

set(CMAKE_CXX_STANDARD 17)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


set(HEADERS
        include/glad/glad.h
        include/KHR/khrplatform.h
        include/shader.h
        include/application.h
        include/stb_image.h)

set(LIBS
        src/shader.cpp
        src/stb_image.cpp)

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/texture/shaders/textureFrag.shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/)
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/texture/shaders/texVertex.shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/)

macro(copy_files files)
    foreach(file ${files})
        message(STATUS "Copying resource ${file}")
        file(COPY ${file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/shaders)
    endforeach()
endmacro()

macro(copy_resources dirs)
    foreach(dir ${dirs})
        string(REGEX REPLACE "/+$" "" dirclean "${dir}")
        message(STATUS "Copying resource ${dirclean}")
        file(COPY ${dirclean} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/)
    endforeach()
endmacro()

copy_resources(resources/)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/src/texture/shaders/)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/shaders/)


#add_executable(OPENGL ${HEADERS} src/draw_triangle.cpp src/glad.c)
#add_executable(OPENGL ${HEADERS} src/draw_rectangle_EBO.cpp src/glad.c)
#add_executable(OPENGL ${HEADERS} src/exercise1.cpp src/glad.c)
#add_executable(OPENGL ${HEADERS} src/exercise2.cpp src/glad.c)
#add_executable(OPENGL ${HEADERS} src/exercise3.cpp src/glad.c)
#add_executable(OPENGL ${HEADERS} ${SOURCE} ${shaders} src/shaders.cpp src/glad.c)
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/texture/textures.cpp src/glad.c)
add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/transformation/glm.cpp src/glad.c)
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/transformation/transformation.cpp src/glad.c)

target_link_libraries(OPENGL ${CONAN_LIBS})
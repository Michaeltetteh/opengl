cmake_minimum_required(VERSION 3.0)
project(OPENGL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


set(HEADERS
        include/glad/glad.h
        include/KHR/khrplatform.h
        include/shader.h
        include/application.h
        include/stb_image.h
        include/camera.h
        include/utils.h
        include/mesh.h
        include/model.h)

set(LIBS
        src/shader.cpp
        src/stb_image.cpp
        src/glad.c)

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
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/shaders/)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/src/texture/shaders/)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/src/transformation/shaders/)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/src/coordinates_system/shaders/)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/src/camera/shaders/)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/src/lighting/shaders/)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/src/model_loading/shaders/)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/src/advanced_opengl/shaders/)

#add_executable(OPENGL ${HEADERS} src/draw_triangle.cpp )
#add_executable(OPENGL ${HEADERS} src/draw_rectangle_EBO.cpp )
#add_executable(OPENGL ${HEADERS} src/exercise1.cpp )
#add_executable(OPENGL ${HEADERS} src/exercise2.cpp )
#add_executable(OPENGL ${HEADERS} src/exercise3.cpp )
#add_executable(OPENGL ${HEADERS} ${SOURCE} ${shaders} src/shaders.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/texture/textures.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/transformation/glm.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/transformation/transformation.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/transformation/ex.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/coordinates_system/coordinate_system.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/coordinates_system/3d.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/camera/camera.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/lighting.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/ambient.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/diffuse.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/specular.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/material.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/diffuse_map.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/specular_map.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/directional_light.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/point_light_attenuation.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/spotlight.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/spotlight_soft_edges.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/lighting/multiple_light_source.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/model_loading/model_loading.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/advanced_opengl/depth_test.cpp )
#add_executable(${PROJECT_NAME} ${HEADERS} ${LIBS} src/advanced_opengl/stencil_testing.cpp )
#add_executable(opengl ${HEADERS} ${LIBS} src/advanced_opengl/blending_discard_fragment.cpp)
#add_executable(opengl ${HEADERS} ${LIBS} src/advanced_opengl/math.cpp)
add_executable(opengl ${HEADERS} ${LIBS} src/advanced_opengl/blending_semi_transparent.cpp)

target_link_libraries(opengl ${CONAN_LIBS})
cmake_minimum_required(VERSION 3.0)
project(OPENGL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


 if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
     find_library(MYGLLIB OpenGL NAMES OpenGL GL gl DOC "Find GL library" REQUIRED)
     if(${MYGLLIB} STREQUAL MYGLLIB-NOTFOUND)
         message(FATAL_ERROR "Could not find library ${MYGLLIB}")
     else()
         message(STATUS "found lib ${MYGLLIB}")
     endif()
 else()
     find_library(MYGLLIB gl NAMES GL DOC "Find GL library" REQUIRED)
     if(${MYGLLIB} STREQUAL MYGLLIB-NOTFOUND) 
         message(FATAL_ERROR "Could not find library ${MYGLLIB}")
     else()
         message(STATUS "found lib ${MYGLLIB}")
     endif()
 endif()


find_package(Git QUIET)
if(GIT_FOUND AND EXISTS ${PROJECT_SOURCE_DIR}/.git)
    option(GIT_SUBMODULES "Check submodules during build" ON)
    if(GIT_SUBMODULES)
        message(STATUS "Updating submodules")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT
        )
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule --init failed with ${GIT_SUBMOD_RESULT}.")
        endif()
    endif()
endif()


#Check for all submodules
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt)
    message(FATAL_ERROR "glfw submodule was not downloaded, GIT_SUBMODULES was turned off or failed")
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/assimp/CMakeLists.txt)
    message(FATAL_ERROR "assimp submodule was not downloaded, GIT_SUBMODULES was turned off or failed")
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/external/glm/CMakeLists.txt)
    message(FATAL_ERROR "glm submodule was not downloaded, GIT_SUBMODULES was turned off or failed")
endif()

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


add_subdirectory(external)
add_subdirectory(libs)

set(GLFW_INC_DIR ${OPENGL_SOURCE_DIR}/external/glfw/include)
set(GLFW_LINK_DIR ${OPENGL_SOURCE_DIR}/external/glfw/include/src)

set(GLM_INC_DIR ${OPENGL_SOURCE_DIR}/external/glm)

set(ASSIMP_INC_DIR ${OPENGL_SOURCE_DIR}/external/assimp/include)
set(ASSIMP_LINK_DIR ${OPENGL_SOURCE_DIR}/external/assimp/)

set(GLAD_INC_DIR ${OPENGL_SOURCE_DIR}/libs/glad)
set(GLAD_LINK_DIR ${OPENGL_SOURCE_DIR}/libs/glad)

set(STB_IMAGE_INC_DIR ${OPENGL_SOURCE_DIR}/libs/stb_image)
set(STB_IMAGE_LINK_DIR ${OPENGL_SOURCE_DIR}/libs/stb_image)



add_subdirectory(src)
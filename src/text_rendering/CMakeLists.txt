cmake_minimum_required(VERSION 3.0)

project(render_text)
include(FetchContent)


FetchContent_Declare(freetype
    GIT_REPOSITORY "https://github.com/freetype/freetype.git"
    GIT_TAG VER-2-13-2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(freetype)

message(STATUS "FreeType include dir: ${freetype_SOURCE_DIR}")

foreach( _target render_text)
    add_executable(${_target} ${APPS_HEADERS} ${_target}.cpp)

    target_include_directories(${_target}
        PUBLIC
            ${GLFW_INC_DIR}
        PRIVATE
            ${GLM_INC_DIR}
        PRIVATE
            ${ASSIMP_INC_DIR}
        PRIVATE
            ${GLAD_INC_DIR}
            ${STB_IMAGE_INC_DIR}
            ${freetype_SOURCE_DIR}/include
    )

    target_link_directories(${_target}
        PRIVATE
            ${GLFW_LINK_DIR}
        PRIVATE
            ${ASSIMP_LINK_DIR}
        PRIVATE
            ${STB_IMAGE_LINK_DIR}
            ${GLAD_LINK_DIR}
    )

    target_link_libraries(${_target}
        ${MYGLLIB}
        glfw
        assimp
        Glad
        stb_image
        freetype
    )

endforeach()
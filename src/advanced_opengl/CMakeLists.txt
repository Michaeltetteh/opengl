project(advanced_opengl)

foreach( _target
        blending_semi_transparent blending_discard_fragment depth_test face_culling math stencil_testing
        framebuffer frame_buffer)
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
    )

endforeach()
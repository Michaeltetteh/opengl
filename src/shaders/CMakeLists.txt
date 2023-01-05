project(shader)


file(GLOB APP_SRC
        "./*.cpp"
        )

foreach( source ${APP_SRC})
    add_executable(${PROJECT_NAME} ${APPS_HEADERS} ${source})

    target_include_directories(${PROJECT_NAME}
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

    target_link_directories(${PROJECT_NAME}
        PRIVATE
            ${GLFW_LINK_DIR}
        PRIVATE
            ${ASSIMP_LINK_DIR}
        PRIVATE
            ${STB_IMAGE_LINK_DIR}
            ${GLAD_LINK_DIR}
        )

    target_link_libraries(${PROJECT_NAME}
        ${MYGLLIB}
        glfw
        assimp
        Glad
        stb_image
    )

endforeach()
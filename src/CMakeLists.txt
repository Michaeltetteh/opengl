
file(GLOB APPS_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/app/*.h")

add_subdirectory(camera)
add_subdirectory(coordinates_system)
add_subdirectory(lighting)
add_subdirectory(model_loading)
add_subdirectory(texture)
add_subdirectory(shaders)
add_subdirectory(transformation)
add_subdirectory(triangle)
add_subdirectory(advanced_opengl)
add_subdirectory(advanced_lighting)
add_subdirectory(debugging)

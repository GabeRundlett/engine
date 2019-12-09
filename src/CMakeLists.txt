link_libraries(glfw glad stb debug_lib dl)
include_directories(engine_include_dir)
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/glfw/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/glad/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/stb/src")
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/debug/include")

set(sources
    plat/opengl/opengl_buffer.cpp
    plat/opengl/opengl_context.cpp
    plat/opengl/opengl_renderer.cpp
    plat/opengl/opengl_shader.cpp
    plat/opengl/opengl_texture.cpp
)

if (WIN32)
    set(sources ${sources} plat/windows/windows_window.cpp)
elseif (APPLE)
    set(sources ${sources})
elseif (UNIX)
    set(sources ${sources} plat/windows/windows_window.cpp)
endif()

add_library(${PROJECT_NAME} ${sources})

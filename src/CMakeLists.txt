
link_libraries(glfw glad stb debug_lib)
include_directories(${engine_include_dir})

set(sources 
    plat/opengl/opengl_buffer.cpp
    plat/opengl/opengl_context.cpp
    plat/opengl/opengl_renderer.cpp
    plat/opengl/opengl_shader.cpp
    plat/opengl/opengl_texture.cpp

    plat/windows/windows_window.cpp
)

add_library(${PROJECT_NAME} ${sources})

link_libraries(glfw glad stb debug1.0.0 dl)

include_directories(
    ${lib_include_dir}
    ${glfw_include_dir}
    ${glad_include_dir}
    ${stb_include_dir}
)

set(sources
    plat/opengl/opengl_buffer.cpp
    plat/opengl/opengl_context.cpp
    plat/opengl/opengl_renderer.cpp
    plat/opengl/opengl_shader.cpp
    plat/opengl/opengl_texture.cpp
)

if (WIN32)
    set(sources ${sources} 
        plat/windows/windows_window.cpp
    )
elseif (APPLE)
    set(sources ${sources}
    )
elseif (UNIX)
    set(sources ${sources} 
        plat/windows/windows_window.cpp
    )
endif()

add_library(${lib_name} ${sources})

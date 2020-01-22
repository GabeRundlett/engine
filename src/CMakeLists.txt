set(Headers
    Buffer.hpp
    Coel.hpp
    Context.hpp
    Core.hpp
    Events.hpp
    Layout.hpp
    Renderer.hpp
    Shader.hpp
    Texture.hpp
    Window.hpp

    Opengl/Common.hpp
)
set(Sources
    Opengl/Buffer.cpp
    Opengl/Context.cpp
    Opengl/Renderer.cpp
    Opengl/Shader.cpp
    Opengl/Texture.cpp
)

if (WIN32)
    set(Sources ${Sources}
        Windows/Window.cpp
    )
elseif (APPLE)
    set(Sources ${Sources}
        Windows/Window.cpp
    )
elseif (UNIX)
    set(Sources ${Sources}
        Windows/Window.cpp
    )
endif()

add_library(Coelengine ${Sources} ${Headers})
target_link_libraries(Coelengine PUBLIC glfw glad math stb)
target_compile_features(Coelengine PUBLIC cxx_std_17)
target_include_directories(Coelengine PUBLIC ${CMAKE_CURRENT_LIST_DIR})

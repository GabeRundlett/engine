cmake_minimum_required(VERSION 3.12)

project(Coelengine VERSION 1.0.0)
enable_testing()

if (NOT TARGET Coelengine)
    add_subdirectory(dep/glfw)
    add_subdirectory(dep/glad)
    add_subdirectory(dep/glm)
    add_subdirectory(dep/imgui)
    add_subdirectory(dep/stb)
    # add_subdirectory(dep/assimp)

    add_subdirectory(src)
    add_subdirectory(test)
endif()

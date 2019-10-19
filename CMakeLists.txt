add_subdirectory(dep/glfw)
add_subdirectory(dep/glad)
add_subdirectory(dep/math)
add_subdirectory(dep/stb)

include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/glfw/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/glad/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/math/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/stb/src")

file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp" "src/*.hpp")
add_library(engine STATIC ${ENGINE_SOURCES})
target_link_libraries(engine general glfw glad math stb)

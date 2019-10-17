include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/glfw/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/glad/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/stb/include")

file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp" "src/*.hpp")
add_library(engine STATIC ${ENGINE_SOURCES})
target_link_libraries(engine general glfw glad stb)

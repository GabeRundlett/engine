cmake_minimum_required(VERSION 3.0.0)
project(engine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(engine_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(dep/glfw)
add_subdirectory(dep/glad)
add_subdirectory(dep/stb)
add_subdirectory(dep/debug)

include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/glfw/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/glad/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/stb/src")
include_directories("${CMAKE_CURRENT_LIST_DIR}/dep/debug/include")
include_directories(engine_include_dir)

add_subdirectory(src)
add_subdirectory(tests)

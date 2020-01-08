cmake_minimum_required(VERSION 3.5)
project(engine VERSION 1.0.0)

set(lib_name ${PROJECT_NAME}${PROJECT_VERSION})
set(lib_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (NOT TARGET ${PROJECT_NAME})
	set(glfw_include_dir ${CMAKE_CURRENT_LIST_DIR}/dep/glfw/include)
	set(glad_include_dir ${CMAKE_CURRENT_LIST_DIR}/dep/glad/include)
	set(stb_include_dir ${CMAKE_CURRENT_LIST_DIR}/dep/stb/src)
	set(debug_include_dir ${CMAKE_CURRENT_LIST_DIR}/dep/debug/include)

	add_subdirectory(dep/glfw)
	add_subdirectory(dep/glad)
	add_subdirectory(dep/stb)

	add_subdirectory(src)

	include(CTest)
	enable_testing()
	add_subdirectory(test)
endif()

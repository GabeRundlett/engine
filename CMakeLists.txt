cmake_minimum_required(VERSION 3.0.0)
project(engine VERSION 0.1.0)

if (NOT TARGET ${PROJECT_NAME})
	set(CMAKE_CXX_STANDARD 17)
	
	set(engine_include_dir ${CMAKE_CURRENT_LIST_DIR}/include)
	set(glfw_include_dir ${CMAKE_CURRENT_LIST_DIR}/dep/glfw/include)
	set(glad_include_dir ${CMAKE_CURRENT_LIST_DIR}/dep/glad/include)
	set(stb_include_dir ${CMAKE_CURRENT_LIST_DIR}/dep/stb/src)
	set(debug_include_dir ${CMAKE_CURRENT_LIST_DIR}/dep/debug/include)

	add_subdirectory(dep/glfw)
	add_subdirectory(dep/glad)
	add_subdirectory(dep/stb)
	add_subdirectory(dep/debug)

	add_subdirectory(src)
	add_subdirectory(tests)
endif()

cmake_minimum_required(VERSION 3.0.0)
project(debug_lib VERSION 0.1.0)

if (NOT TARGET ${PROJECT_NAME})
	set(debug_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")

	add_subdirectory(src)
	add_subdirectory(tests)
endif()

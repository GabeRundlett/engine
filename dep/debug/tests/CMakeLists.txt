include(CTest)

link_libraries(${PROJECT_NAME})
include_directories(${debug_include_dir})

add_executable(debug_master_test master_test.cpp)
add_test(debug_master_test debug_master_test)

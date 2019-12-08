include(CTest)

link_libraries(${PROJECT_NAME})
include_directories(${engine_include_dir})

add_executable(engine_master_test master_test.cpp)
add_test(engine_master_test engine_master_test)

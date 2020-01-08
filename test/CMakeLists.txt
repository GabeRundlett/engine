add_executable(engine_master_test master_test.cpp)
add_test(engine_master_test engine_master_test)

target_link_libraries(engine_master_test PRIVATE ${lib_name})
target_include_directories(engine_master_test PRIVATE ${lib_include_dir})

target_compile_options(engine_master_test PRIVATE -Werror)
target_compile_features(engine_master_test PRIVATE cxx_std_17)

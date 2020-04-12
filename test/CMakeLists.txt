
function(CREATE_COELTEST TEST_NAME)
    add_executable(COELTEST_target_${TEST_NAME} ${TEST_NAME}.cpp)
    target_link_libraries(COELTEST_target_${TEST_NAME} PUBLIC Coelengine)
    add_test(COELTEST_${TEST_NAME} COELTEST_target_${TEST_NAME})
endfunction()

CREATE_COELTEST(Window)
CREATE_COELTEST(Buffers)

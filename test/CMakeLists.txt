cmake_minimum_required(VERSION 3.10)

set(TEST_FILES
    test_sum.c
)

add_executable(test_runner test_runner.c ${TEST_FILES})

target_link_libraries(test_runner PRIVATE collec)

add_custom_target(run-tests
    COMMAND ./test_runner
    DEPENDS test_runner
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running tests..."
)

target_compile_definitions(test_runner PRIVATE 
    TEST_PROJECT_DIR="${CMAKE_CURRENT_BINARY_DIR}"
)

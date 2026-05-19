cmake_minimum_required(VERSION 3.10)

set(TEST_FILES
    test-sum.c
)

add_executable(test-runner test-runner.c ${TEST_FILES})

target_link_libraries(test-runner PRIVATE colle-c)

add_custom_target(run-tests
    COMMAND ./test-runner
    DEPENDS test-runner
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running tests..."
)

target_compile_definitions(test-runner PRIVATE 
    TEST_PROJECT_DIR="${CMAKE_CURRENT_BINARY_DIR}"
)

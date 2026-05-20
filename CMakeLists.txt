cmake_minimum_required(VERSION 3.10)
project(collec)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)

cmake_minimum_required(VERSION 3.10)

add_library(colle-c colle-c.c)
target_include_directories(colle-c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

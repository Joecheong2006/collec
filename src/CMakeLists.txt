cmake_minimum_required(VERSION 3.10)

add_library(colle_c colle_c.c)
target_include_directories(colle_c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

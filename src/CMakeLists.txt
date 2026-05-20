cmake_minimum_required(VERSION 3.10)

add_library(collec collec.c)
target_include_directories(collec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

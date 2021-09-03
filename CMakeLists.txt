cmake_minimum_required(VERSION 3.14)

project(GeminiSim)

include_directories(src)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

add_executable(GeminiSim ${SOURCES})
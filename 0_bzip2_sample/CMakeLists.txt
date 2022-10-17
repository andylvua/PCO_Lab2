cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME "bzip2_sample")
set(LIBRARY_NAME "libbzip2")
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C DESCRIPTION "Second library")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(library)
add_subdirectory(examples)
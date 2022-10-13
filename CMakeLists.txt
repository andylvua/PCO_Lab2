cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME lab1_cstring-zinchukkryvenyaroshevychkharabara)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C CXX DESCRIPTION "POK_LAB2")

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(examples)
add_subdirectory(library)
add_subdirectory(tests)
add_subdirectory(benchmark)

enable_testing()

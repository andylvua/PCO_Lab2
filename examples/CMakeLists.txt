add_executable(example example.cpp)

target_link_libraries(example mystring)
target_link_libraries(example mystring_static)

target_include_directories(example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../library)

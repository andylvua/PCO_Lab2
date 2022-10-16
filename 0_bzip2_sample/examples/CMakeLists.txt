file(GLOB EXAMPLES *.c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

foreach(EXAMPLE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE})
    target_link_libraries(${EXAMPLE_NAME} ${LIBRARY_NAME})
    target_compile_options(${EXAMPLE_NAME} PRIVATE -w)
endforeach()
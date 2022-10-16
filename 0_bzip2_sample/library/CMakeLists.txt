file(GLOB SOURCES *.c)
file(GLOB HEADERS *.h)

add_library(${LIBRARY_NAME}_objects OBJECT ${SOURCES} ${HEADERS})
set_target_properties(${LIBRARY_NAME}_objects PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(${LIBRARY_NAME} SHARED $<TARGET_OBJECTS:${LIBRARY_NAME}_objects>)
add_library(${LIBRARY_NAME}_static STATIC $<TARGET_OBJECTS:${LIBRARY_NAME}_objects>)
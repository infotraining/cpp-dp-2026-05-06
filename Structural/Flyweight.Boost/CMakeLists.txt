##################
# Target
get_filename_component(DIRECTORY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" TARGET_MAIN ${DIRECTORY_NAME})

####################
# Sources & headers
aux_source_directory(. SRC_LIST)
file(GLOB HEADERS_LIST "*.h" "*.hpp")

add_executable(${TARGET_MAIN} ${SRC_LIST} ${HEADERS_LIST})

find_package(Boost REQUIRED)
target_link_libraries(${TARGET_MAIN} PRIVATE Boost::boost)

find_package(Threads REQUIRED)
target_link_libraries(${TARGET_MAIN} PRIVATE Threads::Threads)
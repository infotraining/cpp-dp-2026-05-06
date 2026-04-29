##################
# Target
get_filename_component(DIRECTORY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" TARGET_MAIN ${DIRECTORY_NAME})

#----------------------------------------
# Library - src
#----------------------------------------
add_subdirectory(src)

#----------------------------------------
# Application
#----------------------------------------
add_executable(${TARGET_MAIN} main.cpp)
target_link_libraries(${TARGET_MAIN} turnstile_lib)

#----------------------------------------
# Tests
#----------------------------------------
enable_testing()
add_subdirectory(tests)
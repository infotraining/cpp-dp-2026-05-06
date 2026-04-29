##################
# Target
get_filename_component(DIRECTORY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" TARGET_MAIN ${DIRECTORY_NAME})

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)

####################
# Main app
include_directories(src)  
add_executable(${TARGET_MAIN} main.cpp)
target_compile_features(${TARGET_MAIN} PUBLIC cxx_std_17)
target_link_libraries(${TARGET_MAIN} PUBLIC ${PROJECT_LIB})

# #----------------------------------------
# # set compiler options
# #----------------------------------------
# if (MSVC)
#     target_compile_definitions(${PROJECT_NAME} PRIVATE "/std:c++latest") 
# else ()
#     target_compile_definitions(${PROJECT_NAME} PRIVATE "-Wall") 
# endif()
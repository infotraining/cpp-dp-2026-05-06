set(PROJECT_TEST ${TARGET_MAIN}_tests)
project(PROJECT_TEST)

find_package(Catch2 3)

if (NOT Catch2_FOUND)
  message(STATUS "Catch2 not found, using FetchContent to download it.")
  Include(FetchContent)

  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.10.0 # or a later release
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )

  FetchContent_MakeAvailable(Catch2)

  list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()

include(CTest)
include(Catch)

enable_testing(true)

file(GLOB_RECURSE TEST_SRC_FILES ./*_tests.cpp)

add_executable (${PROJECT_TEST} ${TEST_SRC_FILES})
target_link_libraries(${PROJECT_TEST} ${PROJECT_LIB_NAME} Catch2::Catch2WithMain)
     
catch_discover_tests(${PROJECT_TEST})


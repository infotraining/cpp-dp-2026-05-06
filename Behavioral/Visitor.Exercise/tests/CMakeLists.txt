set(PROJECT_TESTS ${TARGET_MAIN}_tests)
message(STATUS "PROJECT_TESTS is: " ${PROJECT_TESTS})

project(${PROJECT_TESTS} CXX)

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
enable_testing()

file(GLOB TEST_SOURCES *_tests.cpp *_test.cpp)

add_executable(${PROJECT_TESTS} ${TEST_SOURCES})
target_compile_features(${PROJECT_TESTS} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_TESTS} PRIVATE ${PROJECT_LIB} Catch2::Catch2WithMain)

catch_discover_tests(${PROJECT_TESTS})
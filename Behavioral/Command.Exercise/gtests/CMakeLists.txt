set(PROJECT_GTESTS ${TARGET_MAIN}_google_tests)
message(STATUS "PROJECT_GTESTS is: " ${PROJECT_GTESTS})

project(${PROJECT_GTESTS} CXX)

#----------------------------------------
# Google Test
#----------------------------------------
find_package(GTest)

if (NOT GTest_FOUND)
  message(STATUS "GTest not found, using FetchContent to download it.")

  include(FetchContent)
  # FetchContent_Declare(
  #   googletest
  #   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  #   DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  # )
  # # For Windows: Prevent overriding the parent project's compiler/linker settings
  # set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  # FetchContent_MakeAvailable(googletest)
  FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0  # or any stable tag you prefer
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

include(GoogleTest)

enable_testing()        

file(GLOB TEST_SOURCES *_tests.cpp *_test.cpp)

add_executable(${PROJECT_GTESTS} ${TEST_SOURCES})
target_compile_features(${PROJECT_GTESTS} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_GTESTS} PRIVATE ${PROJECT_LIB} GTest::gtest GTest::gmock)

gtest_discover_tests(${PROJECT_GTESTS})
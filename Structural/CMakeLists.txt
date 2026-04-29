# Set VCPKG_ROOT to your vcpkg installation directory or add the following to your cmake call:
# -DCMAKE_TOOLCHAIN=<path_to_vcpkg>/scripts/buildsystems/vcpkg.cmake

cmake_minimum_required(VERSION 3.16)
set(CMAKE_VERBOSE_MAKEFILE ON)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")  
endif()
if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
  set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
endif()

project(dp-structural LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(Adapter.Exercise)
add_subdirectory(Adapter.TheoryCode)
add_subdirectory(Bridge.Pimpl)
add_subdirectory(Bridge.TheoryCode)
add_subdirectory(Composite.Exercise)
add_subdirectory(Composite.TheoryCode)
add_subdirectory(Decorator.Exercise)
add_subdirectory(Decorator.TheoryCode)
add_subdirectory(Facade.TheoryCode)
# add_subdirectory(Flyweight.Boost)
add_subdirectory(Proxy.TheoryCode)
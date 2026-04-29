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

project(dp-behavioral LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(Chain.TheoryCode)
add_subdirectory(Chain.Example)
add_subdirectory(Mediator.TheoryCode)
add_subdirectory(Observer.Exercise)
add_subdirectory(Observer.TheoryCode)
add_subdirectory(State.TheoryCode)
add_subdirectory(Strategy.Exercise)
add_subdirectory(Strategy.TheoryCode)
add_subdirectory(TemplateMethod.TheoryCode)
add_subdirectory(State.Example)
add_subdirectory(State.Exercise)
add_subdirectory(Visitor.Exercise)
add_subdirectory(Command.Exercise)
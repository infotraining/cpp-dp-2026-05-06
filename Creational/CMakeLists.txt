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

project(dp-creational LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(AbstractFactory.Example)
add_subdirectory(AbstractFactory.Exercise)
add_subdirectory(AbstractFactory.TheoryCode)
add_subdirectory(FactoryMethod.Intro)
add_subdirectory(FactoryMethod.Example)
add_subdirectory(FactoryMethod.Exercise1)
add_subdirectory(FactoryMethod.Exercise2)
add_subdirectory(Builder.Example)
add_subdirectory(Builder.Example.SP)
add_subdirectory(Builder.TheoryCode)
add_subdirectory(Prototype.Intro)
add_subdirectory(Prototype.TheoryCode)
add_subdirectory(Prototype.Exercise)
add_subdirectory(Singleton.TheoryCode)
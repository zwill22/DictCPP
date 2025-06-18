cmake_minimum_required(VERSION 3.22)
project(DictCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_library(DictCPP SHARED dictcpp.hpp)
set_target_properties(DictCPP PROPERTIES LINKER_LANGUAGE CXX)

find_package(Catch2 3)
if (${Catch2_DIR} MATCHES "Catch2_DIR_NOTFOUND")
    message(FATAL_ERROR "Catch2 not found -- Cannot build tests")
endif ()

message(STATUS "Catch2_DIR: ${Catch2_DIR}")

include(CTest)
include(Catch)

enable_testing()

add_library(catch SHARED tests/catch.hpp)
target_link_libraries(catch Catch2::Catch2WithMain)
target_include_directories(catch INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)

add_executable(TestDict tests/test_dict.cpp)
target_link_libraries(TestDict catch DictCPP)
catch_discover_tests(TestDict)

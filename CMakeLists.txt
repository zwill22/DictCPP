cmake_minimum_required(VERSION 3.22)
project(DictCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_library(DictCPP INTERFACE)
target_include_directories(DictCPP INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)
set_target_properties(DictCPP PROPERTIES LINKER_LANGUAGE CXX)

find_package(Catch2 3)
if (${Catch2_DIR} MATCHES "Catch2_DIR-NOTFOUND")
    message(FATAL_ERROR "Catch2 not found -- Cannot build tests")
endif ()

message(STATUS "Catch2_DIR: ${Catch2_DIR}")

include(CTest)
include(Catch)

enable_testing()

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE tests)
target_link_libraries(catch INTERFACE Catch2::Catch2WithMain)

add_executable(TestDict tests/test_dict.cpp)
target_link_libraries(TestDict catch DictCPP)
catch_discover_tests(TestDict)

add_executable(TestDirectAccess tests/test_direct.cpp)
target_link_libraries(TestDirectAccess catch DictCPP)
catch_discover_tests(TestDirectAccess)

add_executable(TestDelete tests/test_delete.cpp)
target_link_libraries(TestDelete catch DictCPP)
catch_discover_tests(TestDelete)

add_executable(TestGet tests/test_get.cpp)
target_link_libraries(TestGet catch DictCPP)
catch_discover_tests(TestGet)

add_executable(TestMerging tests/test_merge.cpp)
target_link_libraries(TestMerging catch DictCPP)
catch_discover_tests(TestMerging)

add_executable(TestFunctions tests/test_functions.cpp)
target_link_libraries(TestFunctions catch DictCPP)
catch_discover_tests(TestFunctions)

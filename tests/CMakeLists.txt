find_package(Catch2 3)
if (${Catch2_DIR} MATCHES "Catch2_DIR_NOTFOUND")
    message(FATAL_ERROR "Catch2 not found -- Cannot build tests")
endif ()

message(STATUS "Catch2_DIR: ${Catch2_DIR}")

include(CTest)
include(Catch)

enable_testing()

add_library(catch SHARED catch.hpp)
target_link_libraries(catch Catch2::Catch2WithMain)
target_include_directories(catch INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)

add_executable(TestDict test_dict.cpp)
target_link_libraries(TestDict catch DictCPP)
catch_discover_tests(TestDict)

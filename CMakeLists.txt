cmake_minimum_required(VERSION 3.31)
project(DictCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_library(DictCPP SHARED dictcpp.hpp)
set_target_properties(DictCPP PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)

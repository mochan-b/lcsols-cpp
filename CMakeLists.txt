cmake_minimum_required(VERSION 3.16)

project(lcsols-cpp)
set(CMAKE_CXX_STANDARD 17)

add_library(catch2_main STATIC catch-main.cpp)
target_include_directories(catch2_main PUBLIC catch2/)

add_executable(lcsols_test Solution475Test.cpp)
target_link_libraries(lcsols_test catch2_main)
target_compile_definitions(lcsols_test PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
target_precompile_headers(lcsols_test PRIVATE catch2/catch.hpp)

enable_testing()
add_test(lcsols_test lcsols_test)
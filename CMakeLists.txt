cmake_minimum_required(VERSION 3.16)

project(lcsols-cpp)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES Catch2/2.6.0@catchorg/stable BASIC_SETUP)

set(CMAKE_CXX_STANDARD 17)

add_library(catch2_main STATIC catch-main.cpp)
target_include_directories(catch2_main PUBLIC ${CONAN_INCLUDE_DIRS})

add_executable(lcsols_test Solution475Test.cpp)
target_link_libraries(lcsols_test catch2_main)
target_compile_definitions(lcsols_test PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
target_include_directories(lcsols_test PUBLIC ${CONAN_INCLUDE_DIRS})
#target_precompile_headers(lcsols_test PRIVATE ${CONAN_INCLUDE_DIRS_CATCH2}/catch2/catch.hpp)

enable_testing()
add_test(lcsols_test ./bin/lcsols_test)
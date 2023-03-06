cmake_minimum_required(VERSION 3.24)
project(PSMathLib)

set(CMAKE_CXX_STANDARD 20)

add_executable(PSMathLib main.cpp mathlib.h)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(PSMathLibTest mathlib_test.cpp)
target_link_libraries(PSMathLibTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(PSMathLibTest)
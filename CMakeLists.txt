cmake_minimum_required(VERSION 3.15)
project(Ways_2_0_)

enable_testing()

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)

include_directories(Libs)
include_directories(googletest/googletest/include)

set(SOURCE_FILES Libs/lib.cpp)

add_executable(main main.cpp ${SOURCE_FILES})
add_executable(tests tests.cpp ${SOURCE_FILES})

target_link_libraries(tests gtest)
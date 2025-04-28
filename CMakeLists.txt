cmake_minimum_required(VERSION 3.10)
project(EldenTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
#message(STATUS "GTEST_INCLUDE_DIRS: ${GTEST_INCLUDE_DIRS}")

add_library(eldentree STATIC src/EldenTree.cpp src/God.cpp src/Land.cpp)
add_executable(benchmark test/Benchmark.cpp)
target_link_libraries(benchmark eldentree)
#run-clang-tidy

#add_executable(eldentree_test test/EldenTreeTest.cpp)
#target_link_libraries(eldentree_test eldentree ${GTEST_BOTH_LIBRARIES})


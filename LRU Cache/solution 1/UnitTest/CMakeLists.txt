cmake_minimum_required(VERSION 3.10)

# set the project name
project(lrucachetest VERSION 1.0)

add_executable(lrucachetest ut_cache.cc ../cache.cc)
target_link_libraries(lrucachetest gtest_main)

include(GoogleTest)
gtest_discover_tests(lrucachetest)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)
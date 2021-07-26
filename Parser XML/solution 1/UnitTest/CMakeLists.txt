cmake_minimum_required(VERSION 3.10)

# set the project name
project(xmlparsetest VERSION 1.0)

add_executable(xmlparsetest ut_xmlexpression.cc ../xmlexpression.cc ../xmlparser.cc)
target_link_libraries(xmlparsetest gtest_main)

include(GoogleTest)
gtest_discover_tests(xmlparsetest)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)
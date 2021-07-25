cmake_minimum_required(VERSION 3.10)

# set the project name
project(XmlParserTest VERSION 1.0)

add_executable(XmlParserTest ut_xmlexpression.cc ../xmlexpression.cc ../xmlparser.cc)
target_link_libraries(XmlParserTest gtest_main)

include(GoogleTest)
gtest_discover_tests(XmlParserTest)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)
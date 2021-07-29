cmake_minimum_required(VERSION 3.10)

# set the project name
project(filesearchtest VERSION 1.0)

add_executable(filesearchtest ut_common.cc ut_file_manager.cc ut_file_manager_ext.cc ../file.cc ../file_manager.cc ../file_manager_ext.cc)
target_link_libraries(filesearchtest gtest_main)

include(GoogleTest)
gtest_discover_tests(filesearchtest)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)
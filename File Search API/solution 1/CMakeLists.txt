cmake_minimum_required(VERSION 3.10)

# set the project name
project(filesearch VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(filesearch main.cc file.cc file_manager.cc file_manager_ext.cc)

# Unit Test
enable_testing()
add_subdirectory(UnitTest)
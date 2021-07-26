cmake_minimum_required(VERSION 3.10)

# set the project name
project(OOPros VERSION 1.0)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(GoogleTest)

enable_testing()
add_subdirectory(Parser\ XML)
add_subdirectory(LRU\ Cache)
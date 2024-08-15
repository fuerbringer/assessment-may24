# include
include_directories(include)

# lib
add_library(libpart1 source/hashtable.cpp)
add_executable(part1 source/main.cpp)

# app
target_link_libraries(part1 PRIVATE libpart1)
target_compile_options(part1 PRIVATE -Wall -Wextra -Wpedantic -Werror)

# test
enable_testing()
add_executable(testpart1 test/test.cpp)

# googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
target_link_libraries(testpart1 GTest::gtest_main)
target_link_libraries(testpart1 libpart1)
include(GoogleTest)
gtest_discover_tests(testpart1)

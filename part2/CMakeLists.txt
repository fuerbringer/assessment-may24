# include
include_directories(include)

# lib
add_library(libpart2 source/endpoint.cpp source/aggregatetradeparser.cpp)
add_executable(part2 source/main.cpp)

# app
target_link_libraries(part2 PRIVATE libpart2)
target_compile_options(part2 PRIVATE -Wall -Wextra -Wpedantic -Werror -lcurl -lcurlpp)

# test
enable_testing()
add_executable(testpart2 test/test.cpp)

# googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
target_link_libraries(testpart2 GTest::gtest_main)
target_link_libraries(testpart2 libpart2)
include(GoogleTest)
gtest_discover_tests(testpart2)

# curlpp
include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)
target_link_libraries(libpart2 ${CURLPP_LDFLAGS})


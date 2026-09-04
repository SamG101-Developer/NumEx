# Find and configure GoogleTest.
find_package(GTest REQUIRED)
set(gtest_disable_pthreads on)
set(BUILD_GTEST ON)
set(BUILD_GMOCK OFF)

# Build the test executable.
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(NumExTests ${TEST_SOURCES})
target_link_libraries(NumExTests PRIVATE GTest::gtest_main NumEx)

# Register the tests.
include(GoogleTest)
gtest_discover_tests(NumExTests)

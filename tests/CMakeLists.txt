cmake_minimum_required(VERSION 3.5)
include("${CMAKE_SOURCE_DIR}/CMakeHelpers.cmake")

list_sources(TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable("tests" ${TEST_SOURCES})

target_link_libraries("tests" PRIVATE "${PROJECT_LIBRARY_NAME}")

target_include_directories("tests" PRIVATE ${INCLUDES})
set_target_properties(
    "tests"
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin-tests"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin-tests"
)

include(CTest)
include(Catch)
catch_discover_tests(tests)

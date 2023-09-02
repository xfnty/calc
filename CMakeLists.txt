cmake_minimum_required(VERSION 3.5)
include("${CMAKE_SOURCE_DIR}/CMakeHelpers.cmake")


# ===== Build options ===== #
set(PROJECT_BUILD_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
option(BUILD_SHARED_LIBS "Build shared libs" OFF)
option(BUILD_TESTING "Build tests" ON)
if (MSVC)
    add_compile_options("/wd4267" "/wd4996")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()


# ===== Project ===== #
set(CMAKE_CXX_STANDARD 20)
project("calc" LANGUAGES CXX)


# ===== Third Party libraries ===== #
include_thirdparty("fmt" "include" "fmt")
include_thirdparty("spdlog" "include" "spdlog")
include_thirdparty("expected" "include" "expected")
include_thirdparty("Catch2" "src" "Catch2::Catch2WithMain")


# ===== Source files ===== #
set(SOURCE_MAIN "src/main.cpp")

list_sources(SOURCES "src")
list(FILTER SOURCES EXCLUDE REGEX "main\\.c.*")


# ===== Include directories ===== #
list(APPEND INCLUDES "src")
include_directories(${INCLUDES})


# ===== Link libraries ===== #
list(APPEND LINK_LIBRARIES "")
link_libraries(${LINK_LIBRARIES})


# ===== Targets ===== #
set(PROJECT_LIBRARY_NAME "${PROJECT_NAME}-shared")
if (SOURCES)
    add_library("${PROJECT_LIBRARY_NAME}" STATIC ${SOURCES})
else()
    add_library("${PROJECT_LIBRARY_NAME}" INTERFACE)
endif()

add_executable(${PROJECT_NAME} ${SOURCE_MAIN})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBRARY_NAME})
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BUILD_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BUILD_DIRECTORY}"
)


# ===== Tests ===== #
if (BUILD_TESTING)
    enable_testing()
    add_subdirectory("tests")
endif()

cmake_minimum_required(VERSION 3.15)

include(CTest)
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

add_executable(tests)

file(GLOB TEST_FILES logval.*.cpp)

target_sources(tests
    PRIVATE
    tests.cpp
    ${TEST_FILES}
)

target_link_libraries(tests
    PRIVATE
    Catch2::Catch2WithMain)

target_include_directories(tests
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>/include
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

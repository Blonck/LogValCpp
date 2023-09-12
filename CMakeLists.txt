cmake_minimum_required(VERSION 3.15)

# Only set the cxx_standard if it is not set by someone else
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

project(
  "LogValCpp"
  VERSION 0.0.1
  DESCRIPTION "A header-only C++ library logarithmic arithmetic")

include(Dependencies.cmake)
logvalcpp_setup_dependencies()

add_library(${PROJECT_NAME} INTERFACE)
# add alias so the project can be uses with add_subdirectory
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

include(GNUInstallDirs)

target_include_directories(${PROJECT_NAME} INTERFACE $<INSTALL_INTERFACE:${CMAKE_ISNTALL_INCLUDEDIR}>
                                                     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_${CMAKE_CXX_STANDARD})


enable_testing()
add_subdirectory(test)

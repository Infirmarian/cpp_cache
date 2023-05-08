cmake_minimum_required(VERSION 3.11)
project(cpp_cache VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(cpp_cache main.cpp)
configure_file(Version.h.in Version.h)

add_library(cache INTERFACE)
target_include_directories(cache
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_include_directories(cache INTERFACE "${PROJECT_BINARY_DIR}")
target_include_directories(cpp_cache PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1
)
FetchContent_MakeAvailable(Catch2)
file(GLOB test-sources CONFIGURE_DEPENDS src/tests/*.cpp)
add_executable(tests "${test-sources}")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain cache)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)

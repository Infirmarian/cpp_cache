cmake_minimum_required(VERSION 3.10)
project(cpp_cache VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(cpp_cache main.cpp)
configure_file(Version.h.in Version.h)

target_include_directories(cpp_cache PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
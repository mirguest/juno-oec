
cmake_minimum_required(VERSION 2.8)

# add this options before PROJECT keyword
# disable in source build
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(juno-oec)

add_subdirectory(demo)

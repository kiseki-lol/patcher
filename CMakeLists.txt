cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)

# TODO: This shouldn't be necessary.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

project(Kiseki.Patcher VERSION 1.0.0)

option(COMPILE_PLAYER "Include player-specific code" OFF)
option(COMPILE_SERVER "Include server-specific code" OFF)

add_subdirectory(Kiseki.Patcher)
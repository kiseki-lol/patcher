cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)

project(Kiseki.Patcher VERSION 1.0.0)

option(COMPILE_PLAYER "Include player-specific code" OFF)
option(COMPILE_SERVER "Include server-specific code" OFF)

add_subdirectory(Kiseki.Patcher)
cmake_minimum_required(VERSION 3.19)

project(storm)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-g -O2 -Wall -Werror -Wno-unused)

include_directories(./)

file(GLOB_RECURSE SOURCES "socket/*.cpp" "utility/*.cpp" "task/*.cpp" "thread/*.cpp" "frame/*.cpp" "engine/*.cpp" "plugin/*.cpp" "xml/*.cpp") 

add_executable(server ${SOURCES} server.cpp)
add_executable(client ${SOURCES} client.cpp)

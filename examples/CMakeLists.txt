cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/SimonRussia/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "ef53eaa092c18d1ae26299daa4ea84d0f1d979ef"
)

project(json)

hunter_add_package(jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)

add_executable(pack ${CMAKE_CURRENT_SOURCE_DIR}/sources/pack.cpp)
target_link_libraries(pack jsoncpp_lib_static)

add_executable(unpack ${CMAKE_CURRENT_SOURCE_DIR}/sources/unpack.cpp)
target_link_libraries(unpack jsoncpp_lib_static)

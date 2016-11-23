cmake_minimum_required(VERSION 3.6)
project(share_file)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES server/main.cpp)
add_executable(server ${SOURCE_FILES})

set(SOURCE_FILES client/main.cpp libs/md5/md5.cpp libs/md5/md5.h)
add_executable(client ${SOURCE_FILES})
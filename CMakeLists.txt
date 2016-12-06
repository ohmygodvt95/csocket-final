cmake_minimum_required(VERSION 3.6)
project(share_file)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES
        server/main.cpp server/main.h
        libs/constants.h
        libs/functions/string_helper.h libs/functions/string_helper.cpp
        server/signup_login/signup_login.h server/signup_login/signup_login.cpp
        libs/entity/user.h libs/entity/user.cpp)
add_executable(server ${SOURCE_FILES})

set(SOURCE_FILES
        server/test/test_signup.cpp
        )
add_executable(test_signup_login ${SOURCE_FILES})
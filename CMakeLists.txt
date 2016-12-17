cmake_minimum_required(VERSION 3.6)
project(share_file)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES
        server/main.cpp server/main.h
        libs/constants.h
        libs/functions/string_helper.h libs/functions/string_helper.cpp
        server/signup_login/signup_login.h server/signup_login/signup_login.cpp
        libs/entity/user.h libs/entity/user.cpp
        server/data/list_users.h
        server/fileio/fileio.h server/fileio/fileio.cpp
        server/fileio/transfer.h server/fileio/transfer.cpp
        server/request/request.cpp server/request/request.h
        )

add_executable(server1 ${SOURCE_FILES})

set(SOURCE_FILES
        server/test/test_signup.cpp server/test/test_signup.h
        )
add_executable(test_signup_login ${SOURCE_FILES})

set(SOURCE_FILES
        server/test/test.cpp
        )
add_executable(test_thread ${SOURCE_FILES})
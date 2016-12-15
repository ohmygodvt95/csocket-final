cmake_minimum_required(VERSION 3.6)
project(share_file)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lpthread")

#set(SOURCE_FILES server/main.cpp)
#add_executable(server ${SOURCE_FILES})

set(SOURCE_FILES client/main.cpp libs/md5/md5.cpp libs/md5/md5.h client/signin/signin.cpp
        client/signin/signin.h client/signup/signup.cpp client/signup/signup.h libs/entity/user.cpp
        libs/entity/user.h
        libs/functions/string_helper.cpp libs/functions/string_helper.h
        client/find_file/find_file.cpp client/find_file/find_file.h
        libs/constants.h
        client/share.h)
add_executable(client1 ${SOURCE_FILES})
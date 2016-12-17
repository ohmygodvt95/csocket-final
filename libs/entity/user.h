//
// Created by quangminh on 24/11/2016.
//

#ifndef SHARE_FILE_USER_H
#define SHARE_FILE_USER_H


#include "string.h"
#include "../md5/md5.h"
#include "../constants.h"
#include "../functions/string_helper.h"

using namespace std;

class user {
public:


    static bool check_string(char string[]);

    string username;
    string password;
    int status;
    int client_sock;
    int client_transfer_sock;
};


#endif //SHARE_FILE_USER_H

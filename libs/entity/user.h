//
// Created by quangminh on 24/11/2016.
//

#ifndef SHARE_FILE_USER_H
#define SHARE_FILE_USER_H

#endif //SHARE_FILE_USER_H

#include "string.h"
#include "../libs/md5.h"
#include "../constants.h"
#include "../functions/string_helper.h"
class User {
public:
    static bool checkString(char string[]);

    string username;
    string password;
    int status;
    int clientSock;
};


#endif //SHARE_FILE_USER_H

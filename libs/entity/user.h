//
// Created by lengkeng on 23/11/2016.
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
    User(char username[], char password[]);

    static int checkString(char string);

    char username[100];
    char password[100];
};
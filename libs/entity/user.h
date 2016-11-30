//
// Created by quangminh on 24/11/2016.
//

#ifndef SHARE_FILE_USER_H
#define SHARE_FILE_USER_H

#include "stdio.h"
#include <string.h>
#include <string>
using namespace std;
class user {
public:
    static bool checkString(char string[]);
    string username;
    string password;
    int status;
    int clientSock;
};


#endif //SHARE_FILE_USER_H

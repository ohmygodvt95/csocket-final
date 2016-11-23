//
// Created by lengkeng on 23/11/2016.
//

#include "user.h"

User::User(char *username, char *password) {
    strcpy(User::username, username);
    strcpy(User::password, md5(password));
}
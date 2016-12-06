//
// Created by quangminh on 24/11/2016.
//

#include "user.h"
#include "../md5/md5.h"
#include "../functions/string_helper.h"
//
//user::user(char *username, char *password) {
//    strcpy(user::username, username);
//    strcpy(user::password, md5(password).c_str());
//}

bool user::checkString(char string[]) {

    for (int i = 0; i < strlen(string); i++) {
        char c = toupper(string[i]);
        if (!string_helper::is_digit(c) && !string_helper::is_alphabet(c) && c != '_')
            return false;

    }
    return true;
}


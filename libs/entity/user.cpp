//
// Created by lengkeng on 23/11/2016.
//

#include "user.h"

User::User(char *username, char *password) {
    strcpy(User::username, username);
    strcpy(User::password, md5(password));
}

int User::checkString(char string) {
    for (int i = 0; i < strlen(string); i++) {
        char c = toupper(string[i]);
        if (!is_digit(c) && !is_alphabet(c) && c != '_')
            return FALSE;

    }
    return TRUE;
}
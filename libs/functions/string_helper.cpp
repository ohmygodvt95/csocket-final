//
// Created by lengkeng on 23/11/2016.
//

#include <cstdlib>
#include <cstring>
#include "string_helper.h"

int is_digit(char c) {
    if (c >= '0' && c <= '9')
        return TRUE;
    return FALSE;
}

int is_alphabet(char c) {
    if (c >= 'A' && c <= 'Z')
        return TRUE;
    return FALSE;
}

int get_status_code(char buff[]) {
    if (strlen(buff) < 4) return 0;
    char code[4];
    for (int i = 0; i < 3; i++) {
        code[i] = buff[i];
    }
    code[3] = '\0';
    return atoi(code);
}
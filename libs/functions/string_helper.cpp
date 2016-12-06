//
// Created by lengkeng on 23/11/2016.
//

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

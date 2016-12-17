//
// Created by quangminh on 25/11/2016.
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "string_helper.h"

bool string_helper::is_alphabet(char c) {
    if (c >= 'A' && c <= 'Z')
        return true;
    return false;

}

bool string_helper::is_digit(char c) {
    if (c >= '0' && c <= '9')
        return true;
    return false;


}

int string_helper::readState(char *c) {
    int state;
    char *p;
    p = strtok(c, "|");
    state = atoi(p);
    p = strtok(NULL, "|");
    printf("%s\n", p);
    return state;
}



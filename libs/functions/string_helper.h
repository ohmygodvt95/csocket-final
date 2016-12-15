//
// Created by quangminh on 25/11/2016.
//

#ifndef SHARE_FILE_STRING_HELPER_H
#define SHARE_FILE_STRING_HELPER_H

#include "stdio.h"
#include <string.h>
#include <string>
#include <list>

using namespace std;

class string_helper {
public:
    static bool is_digit(char c);
    static bool is_alphabet(char c);
    static int readState(char c[]);

};


#endif //SHARE_FILE_STRING_HELPER_H

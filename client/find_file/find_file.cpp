//
// Created by lengkeng on 23/11/2016.
//

#include "find_file.h"


int check_file_exist(char file_name[]) {
    FILE *f;
    f = fopen(file_name, "r");
    if (f == NULL) return FALSE;
    else {
        fclose(f);
        return TRUE;
    }
}
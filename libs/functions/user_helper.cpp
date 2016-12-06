//
// Created by lengkeng on 30/11/2016.
//

#include "user_helper.h"

int check_username_password(char u[], char p[]) {
    FILE *f;
    char user[100];
    char pass[100];
    f = fopen(DATA_FILE, "r+");
    if (f == NULL) return 0;
    while (!feof(f)) {
        if (fscanf(f, "%s %s\n", user, pass) > 1) {
            if (strcmp(u, user) == 0 && strcmp(p, pass) == 0) {
                fclose(f);
                return 1;
            }
        }
    }
    fclose(f);
    return 0;
}


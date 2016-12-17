//
// Created by lengkeng on 06/12/2016.
//

#ifndef SHARE_FILE_SIGNUP_H
#define SHARE_FILE_SIGNUP_H


#include "../../libs/entity/user.h"

class signup_login {
public:
    static void *signup_login_thread(void *us);

    static char *get_username(char buff[]);

    static char *get_password(char buff[]);

    static bool check_username_exist(char buff[]);

    static bool create_user(char buff[]);

    static bool check_login(char buff[]);

    static bool check_logged(char *buff);
};


#endif //SHARE_FILE_SIGNUP_H

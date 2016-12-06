//
// Created by lengkeng on 06/12/2016.
//

#ifndef SHARE_FILE_SIGNUP_H
#define SHARE_FILE_SIGNUP_H


#include "../../libs/entity/user.h"

class signup_login {
public:
    static void signup_login_thread(user u, int server_socket);
};


#endif //SHARE_FILE_SIGNUP_H

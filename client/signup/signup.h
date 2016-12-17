//
// Created by quangminh on 24/11/2016.
//

#ifndef SHARE_FILE_SIGNUP_H
#define SHARE_FILE_SIGNUP_H

#include "stdio.h"
#include <stdlib.h>

using namespace std;

#include "../../libs/entity/user.h"
#include "../../libs/constants.h"
class signup {
public:
    static int sign(int client_sock);
};


#endif //SHARE_FILE_SIGNUP_H

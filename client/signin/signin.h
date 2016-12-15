//
// Created by quangminh on 24/11/2016.
//

#ifndef SHARE_FILE_SIGNIN_H
#define SHARE_FILE_SIGNIN_H

#include "stdio.h"
#include <stdlib.h>
using namespace std;
#include "../../libs/entity/user.h"
#include "../../libs/constants.h"
class signin {
public:
    static void showView(int *state,int client_sock);
    static user  sign_in(int *state,int client_sock);

};


#endif //SHARE_FILE_SIGNIN_H

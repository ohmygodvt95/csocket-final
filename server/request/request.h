//
// Created by lengkeng on 13/12/2016.
//

#ifndef SHARE_FILE_REQUEST_H
#define SHARE_FILE_REQUEST_H


#include "../../libs/entity/user.h"
#include "../../libs/constants.h"

class request {
public:
    static void file_request(user u);

    static char *get_keyword(char buff[]);

    static char *get_username(char buff[]);

    static int is_exist(char buff[]);

    static char *get_last(char *buff);
};


#endif //SHARE_FILE_REQUEST_H

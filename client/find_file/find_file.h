//
// Created by quangminh on 29/11/2016.
//

#ifndef SHARE_FILE_FIND_FILE_H
#define SHARE_FILE_FIND_FILE_H

#include "stdio.h"
#include <iostream>
#include <sys/socket.h>
#include <sstream>

using namespace std;

class find_file {
public:
    static void findFileWithKeyword(int client_sock, int client_transfer_sock);

    static bool checkExistFile(char *fileName);
};


#endif //SHARE_FILE_FIND_FILE_H

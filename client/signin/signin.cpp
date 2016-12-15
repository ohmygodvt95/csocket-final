//
// Created by quangminh on 24/11/2016.
//

#include <iostream>
#include <sys/socket.h>
#include <sstream>
#include "signin.h"
#include "../../libs/functions/string_helper.h"

void signin::showView(int *state, int client_sock) {

}

user signin::sign_in(int *state, int client_sock) {
    string username;
    user u;
    u.status = 0;
    string protocolCall;
    char buff[1024];
    string password;

    stringstream convert;
    convert << SIGN_IN;
    protocolCall += convert.str();
    printf("Insert username\n");
    cin >> username;
    protocolCall += "|" + username;
    printf("Insert password\n");
    cin >> password;
    protocolCall += "|" + password;

    int bytes_sent = send(client_sock, protocolCall.c_str(), protocolCall.length(),
                          0); /* send to the client welcome message */
    int bytes_received = recv(client_sock, buff, 1024, 0);
    cout << buff << endl;
    buff[bytes_received] = '\0';
    int codeStatus = string_helper::readState(buff);
    if (codeStatus == 106) {
        *state *= 10;
        u.password = password;
        u.username = username;
        u.status = 1;

    } else {
        *state = 0;
    }

    return u;
}


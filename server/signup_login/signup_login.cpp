//
// Created by lengkeng on 06/12/2016.
//
#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <zconf.h>
#include "signup_login.h"
#include "../../libs/entity/user.h"

using namespace std;

void signup_login::signup_login_thread(user u, int server_socket) {
//    init
    cout << "Thread " << u.client_sock << endl;
    string welcome_message = "Welcome to my server!";
    int bytes_sent, bytes_recv;
    char buff[1024];
    u.status = 0;
//    send welcome
    send(u.client_sock, welcome_message.c_str(), strlen(welcome_message.c_str()), 0);

    while (u.status == 0) {
        bytes_recv = recv(u.client_sock, buff, 1024, 0);
        buff[bytes_recv] = '\0';
        if (bytes_sent < 0) {
            printf("\nError!Can not sent data to client!");
            close(u.client_sock);
            pthread_exit(NULL);
        }
        cout << buff << endl;
    }

}
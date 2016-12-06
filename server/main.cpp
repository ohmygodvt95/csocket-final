//
//  Le Vinh Thien 12/10/2016
//
#include <iostream>
#include <string.h>   //strlen
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <list>
#include <thread>
#include "main.h"
#include "signup_login/signup_login.h"

using namespace std;

int main(int argc, char *argv[]) {
    /*init*/
    int server_socket, new_socket;
    struct sockaddr_in server; /* server's address information */
    struct sockaddr_in client; /* client's address information */
    list <user> list_users;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  /* calls socket() */
        printf("socket() error\n");
        return (-1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_SIGNUP_LOGIN);   /* Remember htons() from "Conversions" section? =) */
    server.sin_addr.s_addr = INADDR_ANY;  /* INADDR_ANY puts your IP address automatically */
    bzero(&(server.sin_zero), 8); /* zero the rest of the structure */

    if (bind(server_socket, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) { /* calls bind() */
        printf("bind() error\n");
        return (-1);
    }

    if (listen(server_socket, 100) == -1) {  /* calls listen() */
        printf("listen() error\n");
        return (-1);
    }


    while (true) {
        if ((new_socket = accept(server_socket, (struct sockaddr *) &client,
                                 (socklen_t *) sizeof(struct sockaddr_in))) == -1) { /* calls accept() */
            printf("accept() error\n");
            return (-1);
        }

        printf("You got a connection from %s\n", inet_ntoa(client.sin_addr)); /* prints client's IP */
        user u;
        u.client_sock = new_socket;
        thread thread_signup_login(signup_login::signup_login_thread, u, server_socket);
        thread_signup_login.join();
    }

    return 0;
}
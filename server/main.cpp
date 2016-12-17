//
//  Le Vinh Thien 12/10/2016
//
#include <iostream>
#include <string.h>   //strlen
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <list>
#include <pthread.h>
#include "main.h"
#include "signup_login/signup_login.h"
#include "data/list_users.h"
#include "fileio/fileio.h"

using namespace std;
list <user> list_users;
int main(int argc, char *argv[]) {
    /*init*/
    int opt = 1;
    int server_socket, new_socket;
    struct sockaddr_in server; /* server's address information */
    struct sockaddr_in client; /* client's address information */


    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  /* calls socket() */
        printf("socket() error\n");
        return (-1);
    }

    //set master socket to allow multiple connections , this is just a good habit, it will work without this
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
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

    pthread_t thread_tranfer;
    pthread_create(&thread_tranfer, NULL, fileio::transfer_file_server, NULL);

    while (true) {
        int sin_size = sizeof(struct sockaddr_in);
        if ((new_socket = accept(server_socket, (struct sockaddr *) &client,
                                 (socklen_t *) &sin_size)) == -1) { /* calls accept() */
            printf("accept() error\n");
            return (-1);
        }

        printf("You got a connection from %s\n", inet_ntoa(client.sin_addr)); /* prints client's IP */
        user u;
        u.client_sock = new_socket;
        list_users.push_front(u);
        pthread_t thread_signup_login;
        pthread_create(&thread_signup_login, NULL, signup_login::signup_login_thread, &u);
    }

    return 0;
}
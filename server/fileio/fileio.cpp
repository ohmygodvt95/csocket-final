//
// Created by lengkeng on 06/12/2016.
//

#include "fileio.h"
#include <iostream>
#include <string.h>   //strlen
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <list>
#include <pthread.h>
#include "../data/list_users.h"
#include "transfer.h"

void *fileio::transfer_file_server(void *u) {
    /*init*/
    int opt = 1;
    int server_socket, new_socket;
    struct sockaddr_in server; /* server's address information */
    struct sockaddr_in client; /* client's address information */


    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  /* calls socket() */
        printf("socket() error\n");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections , this is just a good habit, it will work without this
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_TRANFER_FILE);   /* Remember htons() from "Conversions" section? =) */
    server.sin_addr.s_addr = INADDR_ANY;  /* INADDR_ANY puts your IP address automatically */
    bzero(&(server.sin_zero), 8); /* zero the rest of the structure */

    if (bind(server_socket, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) { /* calls bind() */
        printf("bind() error\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 100) == -1) {  /* calls listen() */
        printf("listen() error\n");
        exit(EXIT_FAILURE);
    }

    while (true) {
        int sin_size = sizeof(struct sockaddr_in);
        if ((new_socket = accept(server_socket, (struct sockaddr *) &client,
                                 (socklen_t *) &sin_size)) == -1) { /* calls accept() */
            printf("accept() error\n");
            exit(EXIT_FAILURE);
        }
        string welcome_message = "Welcome to my transfer server!";
        int bytes_sent, bytes_recv;
        char buff[1024];
        send(new_socket, welcome_message.c_str(), strlen(welcome_message.c_str()), 0);

        bytes_recv = (int) read(new_socket, buff, 1024);
        buff[bytes_recv] = '\0';
        list<user>::iterator a = list_users.begin();
        for (a; a != list_users.end(); a++) {
            if (strcmp(buff, a->username.c_str()) == 0) {
                a->client_transfer_sock = new_socket;
                user u = *a;
                pthread_t thread_transfer;
                pthread_create(&thread_transfer, NULL, transfer::transfer_thread, &u);
                break;
            }
        }

    }
}
//
//  Le Vinh Thien 12/10/2016
//
#include <iostream>
#include <string.h>   //strlen
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include "main.h"

using namespace std;
#define PORT 5500

char *get_file_name(int i) {
    char *s;
    s = (char *) malloc(sizeof(char) * 20);
    strcpy(s, "tmp_ .txt\0");
    s[4] = char(48 + i);
    return s;
}

int main(int argc, char *argv[]) {
    int opt = TRUE;
    int master_socket, addrlen, new_socket, client_socket[30], max_clients = 30, activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;
    FILE *f[100];
    int status[100];
    char buffer[1025];

    //set of socket descriptors
    fd_set readfds;


    char *message = "Welcome my server";

    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }

    //create a master socket
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections , this is just a good habit, it will work without this
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //bind the socket to localhost port 5500
    if (bind(master_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while (TRUE) {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;
        struct timeval tv;
        tv.tv_sec = 10;
        tv.tv_usec = 500000;
        //add child sockets to set
        for (i = 0; i < max_clients; i++) {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if (sd > 0)
                FD_SET(sd, &readfds);

            //highest file descriptor number, need it for the select function
            if (sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        activity = select(max_sd + 1, &readfds, NULL, NULL, &tv);

        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }

        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            printf("New connection , socket fd is %d , ip is : %s , port : %d \n", new_socket,
                   inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            if (send(new_socket, message, strlen(message), 0) != strlen(message)) {
                perror("send");
            }

            puts("Welcome message sent successfully");
            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++) {
                //if position is empty
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    f[i] = fopen(get_file_name(i), "w+");
                    status[i] = 0;
                    printf("Adding to list of sockets as %d\n", i);
                    break;
                }
            }
        }
        //else its some IO operation on some other socket :)
        for (i = 0; i < max_clients; i++) {

            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                //Check if it was for closing , and also read the incoming message
                if (status[i] == 0) {
                    if ((valread = recv(sd, buffer, 1024, 0)) != 1024) {
                        buffer[valread] = '\0';
                        fputs(buffer, f[i]);
                        status[i] = 1;
                        rewind(f[i]);
                        send(sd, "OK", 3, 0);
                    } else {
                        buffer[valread] = '\0';
                        fputs(buffer, f[i]);

                    }
                } else if (status[i] == 1) {
                    valread = recv(sd, buffer, 1024, 0);
                    char buff[1024];
                    int count = fread(buff, sizeof(char), 1024, f[i]);
                    buff[count] = '\0';
                    send(sd, buff, strlen(buff), 0);
                    if (count != 1024) status[i] = 2;
                }
                else{
                    valread = recv(sd, buffer, 3, 0);
                    getpeername(sd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
                    printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr),
                           ntohs(address.sin_port));
                    close(sd);
                    client_socket[i] = 0;
                    fclose(f[i]);
                    status[i] = 0;
                }
            }
        }
    }

    return 0;
}
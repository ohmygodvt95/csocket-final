//
// Created by lengkeng on 23/11/2016.
//

#include "main.h"
//
// Created by lengkeng on 12/10/2016.
//
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <arpa/inet.h>
using namespace std;
#define PORT 5500
#define BACKLOG 20
#define SIGN_SUCCESS "success"
#define SIGN_FAILURE "failure"
#define SIGN_LOCKED "locked"
void sig_chld(int signo) {
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("[ForkingServer] Child %d terminated\n", pid);
}

int check_exits_username(char s[]){
    FILE * f;
    char user[100];
    char pass[100];
    f = fopen("users.txt", "r+");
    if(f == NULL) return 0;
    while(!feof(f)){
        if(fscanf(f,"%s %s\n", user, pass) > 1){
            if(strcmp(user, s) == 0) {
                fclose(f);
                return 1;
            }
        }
    }
    fclose(f);
    return 0;
}
int check_username_password(char u[], char p[]){
    FILE * f;
    char user[100];
    char pass[100];
    f = fopen("users.txt", "r+");
    if(f == NULL) return 0;
    while(!feof(f)){
        if(fscanf(f,"%s %s\n", user, pass) > 1){
            if(strcmp(u, user) == 0 && strcmp(p, pass) == 0) {
                fclose(f);
                return 1;
            }
        }
    }
    fclose(f);
    return 0;
}
int main() {

    int listen_sock, conn_sock; /* file descriptors */
    char recv_data[1024];
    int bytes_sent;
    struct sockaddr_in server; /* server's address information */
    struct sockaddr_in client; /* client's address information */
    pid_t pid;
    int sin_size;

    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  /* calls socket() */
        printf("socket() error\n");
        exit(-1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
    server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */

    if (bind(listen_sock, (struct sockaddr *) &server, sizeof(server)) == -1) { /* calls bind() */
        printf("bind() error\n");
        exit(-1);
    }

    if (listen(listen_sock, BACKLOG) == -1) {  /* calls listen() */
        printf("listen() error\n");
        exit(-1);
    }

    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        if ((conn_sock = accept(listen_sock, (struct sockaddr *) &client, (socklen_t *) &sin_size)) ==
            -1) { /* calls accept() */
            printf("accept() error\n");
            exit(-1);
        }

        if ((pid = fork()) == 0) {
            int stage = 0;
            int bytes_received;
            char buff[1024];
            char user[100];
            int locked = 5;
            FILE *f;
            close(listen_sock);
            printf("You got a connection from %s\n", inet_ntoa(client.sin_addr)); /* prints client's IP */
            bytes_sent = send(conn_sock, "Welcome to my server.\n", 22, 0); /* send to the client welcome message */
            if (bytes_sent < 0) {
                printf("\nError!Can not sent data to client!");
                close(conn_sock);
                continue;
            }
            while(stage == 0){
                bytes_received = recv(conn_sock, buff, 1024, 0);
                if(bytes_received < 0){
                    printf("\nError!Cannot receive data from sever!\n");
                    close(conn_sock);
                    exit(0);
                }
                else{
                    buff[bytes_received] = '\0';
                    if(check_exits_username(buff)) {
                        stage = 1;
                        strcpy(user, buff);
                        bytes_sent = send(conn_sock, SIGN_SUCCESS, strlen(SIGN_SUCCESS), 0);
                    }
                    else{
                        bytes_sent = send(conn_sock, SIGN_FAILURE, strlen(SIGN_FAILURE), 0);
                    }
                    if (bytes_sent < 0) {
                        printf("\nError!Can not sent data to client!");
                        close(conn_sock);
                        continue;
                    }
                }
            }
            while(stage == 1){
                bytes_received = recv(conn_sock, buff, 1024, 0);
                if(bytes_received < 0){
                    printf("\nError!Cannot receive data from sever!\n");
                    close(conn_sock);
                    exit(0);
                }
                else{
                    buff[bytes_received] = '\0';
                    if(check_username_password(user, buff)) {
                        stage = 2;
                        bytes_sent = send(conn_sock, SIGN_SUCCESS, strlen(SIGN_SUCCESS), 0);
                        cout << user << " authenticated" << endl;
                    }
                    else{
                        if(--locked != 1) bytes_sent = send(conn_sock, SIGN_FAILURE, strlen(SIGN_FAILURE), 0);
                        else {
                            stage = 3;
                            bytes_sent = send(conn_sock, SIGN_LOCKED, strlen(SIGN_LOCKED), 0);
                        }
                    }
                    if (bytes_sent < 0) {
                        printf("\nError!Can not sent data to client!");
                        close(conn_sock);
                        continue;
                    }
                }
            }
            exit(0);
        }

        signal(SIGCHLD, sig_chld);

        close(conn_sock);
    }
    close(listen_sock);
    return 1;
}



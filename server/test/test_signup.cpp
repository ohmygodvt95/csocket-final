//
// Created by lengkeng on 21/09/2016.
//
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <zconf.h>
#include "test_signup.h"
using namespace std;

int main() {
    int client_sock;
    char buff[1024];
    struct sockaddr_in server_addr;
    int bytes_sent, bytes_received;
    long total = 0;
    client_sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5500);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) != 0) {
        printf("\nError!Can not connect to sever!Client exit imediately! ");
        return 0;
    }

    bytes_received = recv(client_sock, buff, 1024, 0);
    if (bytes_received == -1) {
        printf("\nError!Cannot receive data from sever!\n");
        close(client_sock);
        return (-1);
    } else {
        buff[bytes_received] = '\0';
        cout << buff << endl;
        do {
            if (strcmp(buff, "Q") == 0) {
                close(client_sock);
                cout << "send: " << total << " bytes" << endl;
                return 0;
            }
            printf("\nInsert string to send:");
            cin >> buff;

            cout << buff << endl;
            bytes_sent = send(client_sock, buff, strlen(buff), 0);
            total += bytes_sent;
            if (bytes_sent == -1) {
                printf("\nError!Cannot send data to sever!\n");
                close(client_sock);
                return (-1);
            } else {
                bytes_received = recv(client_sock, buff, 1024, 0);
                if (bytes_received == -1) {
                    printf("\nError!Cannot receive data from sever!\n");
                    close(client_sock);
                    return (-1);
                }
                buff[bytes_received] = '\0';
                cout << buff << endl;
            }

        } while (bytes_received);

    }

    close(client_sock);
    return 0;
}

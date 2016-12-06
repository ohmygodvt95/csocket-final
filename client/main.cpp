//

#include "main.h"
#include "signin/signin.h"
#include "find_file/find_file.h"
//
//

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <zconf.h>
#define SIGN_SUCCESS "success"
#define SIGN_FAILURE "failure"
#define SIGN_LOCKED "locked"

using namespace std;

int main(){
    int client_sock;
    char buff[1024];
    FILE *f;

    struct sockaddr_in server_addr;
    int bytes_sent,bytes_received;
    int stage = 0;
    client_sock=socket(AF_INET,SOCK_STREAM,0);

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
    }

    char c, ch;
    c = '0';
    int state = 0;
    do {
        if (state < 10) {
            printf("chuong trinh chia se file\n");
            printf("1:Sign In\n2:Sign Up\nq:quit\n");
            do {
                c = getchar();
                state = state * 10 + (c - '0');
                while (getchar() != '\n');
                if (c != '1' && c != '2' && c != 'q')printf("moi nhap lai\n");

            } while (c != '1' && c != '2' && c != 'q');
            switch (c) {
                case '1':
                    //signin::showView();
                    signin::sign_in(&state, client_sock);
                    break;
                case '2':
                    break;
                case 'q':
                    state = -1;
                    break;
            }
        } else if (state >= 10) {
            printf("1:Find file\nq:log out\n");
            do {
                c = getchar();
                state = state * 10 + (c - '0');
                while (getchar() != '\n');
                if (c != '1' && c != 'q')printf("moi nhap lai\n");

            } while (c != '1' && c != 'q');
            switch (c) {
                case '1':
                    // find_file::findFileWithKeyword(client_sock);
                    break;
                case 'q':
                    state = 0;
                    break;
            }
        }
    } while (state != -1);


/*
    if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
        printf("\nError!Can not connect to sever!Client exit imediately! ");
        return 0;
    }

    bytes_received = recv(client_sock, buff, 1024, 0);
    if(bytes_received == -1){
        printf("\nError!Cannot receive data from sever!\n");
        close(client_sock);
        return(-1);
    }else{
        buff[bytes_received] = '\0';
        puts(buff);
        buff[0] = '\0';
        while(stage == 0){
            cout << "Username: " << endl;
            cin >> buff;
            bytes_sent = send(client_sock, buff, strlen(buff), 0);
            if (bytes_sent < 0) {
                printf("\nError!Can not sent data to client!");
                close(client_sock);
                continue;
            }
            bytes_received = recv(client_sock, buff, 1024, 0);
            if(bytes_received == -1){
                printf("\nError!Cannot receive data from sever!\n");
                close(client_sock);
                return(-1);
            }
            else{
                buff[bytes_received] = '\0';
                if(strcmp(buff, SIGN_SUCCESS) == 0) stage = 1;
                else{
                    cout << "ERROR! Username wrong!" << endl;
                };
            }

        }
        while(stage == 1){
            cout << "Password: " << endl;
            cin >> buff;
            bytes_sent = send(client_sock, md5(buff).c_str(), strlen(md5(buff).c_str()), 0);
            if (bytes_sent < 0) {
                printf("\nError!Can not sent data to client!");
                close(client_sock);
                continue;
            }
            bytes_received = recv(client_sock, buff, 1024, 0);
            if(bytes_received == -1){
                printf("\nError!Cannot receive data from sever!\n");
                close(client_sock);
                return(-1);
            }
            else{
                buff[bytes_received] = '\0';
                if(strcmp(buff, SIGN_SUCCESS) == 0) {
                    stage = 2;
                    cout << "SUCCESS! You login successful" << endl;
                }
                else if(strcmp(buff, SIGN_LOCKED) == 0){
                    stage = 3;
                    cout << "WARNING! You have been locked in 30mins" << endl;
                }
                else cout << "ERROR! Password wrong!" << endl;
            }

        }
    }

    close(client_sock);*/
    return 0;
}

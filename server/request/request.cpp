//
// Created by lengkeng on 13/12/2016.
//

#include "request.h"
#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <zconf.h>
#include "../data/list_users.h"
#include "../request/request.h"

using namespace std;

void request::file_request(user u) {
    int bytes_recv;
    char buff[1024];
    list<user>::iterator a = list_users.begin();
    while (true) {
        bytes_recv = (int) recv(u.client_sock, buff, 1024, 0);
        buff[bytes_recv] = '\0';
//        cout << buff << endl;
        if (bytes_recv == 0) {
            cout << u.username << " was disconnected" << endl;
            close(u.client_sock);
            list<user>::iterator a = list_users.begin();
            for (a; a != list_users.end(); a++) {
                if (a->client_sock == u.client_sock) {
                    a->status = 0;
                    a->username = "";
                }
            }
            pthread_exit(NULL);
        } else {
            string mess = "\0";
            switch (get_status_code(buff)) {
                case FIND_FILE_RESPONSE_FROM_CLIENT:
                    mess = to_string(FIND_FILE_RESPONE_TO_CLIENT) + "|" + u.username + "|" +
                           to_string(request::is_exist(buff)) + "@";
//                    cout << buff << endl;
                    a = list_users.begin();
                    for (a; a != list_users.end(); a++) {
                        if (a->status == AUTH_SUCCESS && strcmp(a->username.c_str(), get_username(buff)) == 0) {

//                            cout << mess << endl;
                            send(a->client_sock, mess.c_str(), strlen(mess.c_str()), 0);
                            cout << "Send result from " << u.username << " to " << a->username << " " + mess << endl;
                            break;
                        }
                    }
                    break;

                case SELECT_FILE_FROM_CLIENT:
                    cout << get_last(buff) << endl;
                    mess = to_string(SELECT_FILE_TO_CLIENT) + "|" + u.username + "|" + request::get_last(buff);

                    a = list_users.begin();
                    for (a; a != list_users.end(); a++) {
                        if (a->status == AUTH_SUCCESS && strcmp(a->username.c_str(), get_username(buff)) == 0) {
                            cout << "Send request get file from " << u.username << " to " << a->username << endl;
//                            cout << mess << endl;
                            send(a->client_transfer_sock, mess.c_str(), strlen(mess.c_str()) + 1, 0);
                            break;
                        }
                    }
                    break;

                case FILE_TRANSFER_FROM_CLIENT:
                    mess = to_string(SELECT_FILE_TO_CLIENT) + "|" + u.username + "|" + request::get_last(buff);
                    break;

                case FIND_FILE_REQUEST_TO_SERVER:
//                    cout << buff << endl;
                    mess = to_string(FIND_FILE_REQUEST_TO_CLIENT) + "|" + u.username + "|" +
                           request::get_keyword(buff);

                    int total = 0;

                    a = list_users.begin();
                    for (a; a != list_users.end(); a++) {
                        if (a->status == AUTH_SUCCESS && a->client_sock != u.client_sock) {
                            total++;
                        }
                    }

                    string mess1 = to_string(FIND_FILE_INFO) + "|" + to_string(total);

                    send(u.client_sock, mess1.c_str(), strlen(mess1.c_str()), 0);
                    cout << "Send info to: " << u.username << endl;

                    a = list_users.begin();
                    for (a; a != list_users.end(); a++) {
                        if (a->status == AUTH_SUCCESS && a->client_sock != u.client_sock) {
                            cout << "Send request find file from " << u.username << " to " << a->username << endl;
//                            cout << mess << endl;
                            send(a->client_sock, mess.c_str(), strlen(mess.c_str()), 0);
                        }
                    }

                    break;

            }
        }
    }
}

char *request::get_keyword(char *buff) {
    char *s;
    s = (char *) malloc(sizeof(char) * 100);
    int n, j = 0;
    for (n = 0; buff[n] != '|'; n++);
    for (int i = n + 1; i < strlen(buff); i++) {
        s[j++] = buff[i];
    }
    s[j] = '\0';
    return s;
}

char *request::get_last(char *buff) {
    char *s;
    s = (char *) malloc(sizeof(char) * 1025);
    int n, j = 0;
    for (n = strlen(buff); buff[n] != '|'; n--);
    for (int i = n + 1; i < strlen(buff); i++) {
        s[j++] = buff[i];
    }
    s[j] = '\0';
    return s;
}

char *request::get_username(char *buff) {
    char *s;
    s = (char *) malloc(sizeof(char) * 100);
    int j = 0;
    for (int i = 4; i < strlen(buff); i++) {
        if (buff[i] != '|' && buff[i] != '\0') {
            s[j++] = buff[i];
        } else {
            s[j] = '\0';
            return s;
        }
    }
    return s;
}

int request::is_exist(char *buff) {
    int n, j = 0;
    char *s;
    s = (char *) malloc(sizeof(char) * 100);
    for (n = strlen(buff); buff[n] != '|'; n--);
    for (int i = n + 1; i < strlen(buff); i++) {
        s[j++] = buff[i];
    }
    s[j] = '\0';
    return atoi(s);
}



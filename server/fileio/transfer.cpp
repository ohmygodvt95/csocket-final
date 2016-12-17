//
// Created by lengkeng on 14/12/2016.
//

#include "transfer.h"
#include <iostream>
#include <string.h>   //strlen
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <list>
#include <pthread.h>
#include "../data/list_users.h"
#include "transfer.h"
#include "../request/request.h"

void *transfer::transfer_thread(void *us) {
    user u = *(user *) us;
    cout << u.username << " connected transfer server! on thread: " << u.client_transfer_sock << endl;

    while (true) {
        char buff[2024];
        int bytes_recv = (int) recv(u.client_transfer_sock, buff, 2024, 0);

//        cout << buff << endl;
        if (bytes_recv == 0) {

            cout << u.username << " was disconnected transfer server" << endl;
            close(u.client_sock);
            close(u.client_transfer_sock);

            list<user>::iterator a = list_users.begin();
            for (a; a != list_users.end(); a++) {
                if (a->client_sock == u.client_sock) {
                    a->status = 0;
                    a->username = "";
                }
            }
            pthread_exit(NULL);
        } else {
            buff[bytes_recv] = '\0';
//            cout << get_status_code(buff) << endl;
            string mess;
            list<user>::iterator a;
            switch (get_status_code(buff)) {
                case SELECT_FILE_FROM_CLIENT:
                    mess = to_string(FILE_TRANSFER_TO_CLIENT) + "|" + u.username + "|" + get_filename(buff) + "|" +
                           request::get_last(buff);
//                    cout << "send request get file " << get_filename(buff) << request::get_last(buff) << request::get_username(buff) << endl;
                    a = list_users.begin();
                    for (a; a != list_users.end(); a++) {
                        if (strcmp(a->username.c_str(), request::get_username(buff)) == 0) {
//                            cout << "send request get file " << get_filename(buff) << request::get_last(buff) << endl;
                            send(a->client_transfer_sock, mess.c_str(), strlen(mess.c_str()), 0);
                            break;
                        }
                    }
                    break;
                case FILE_TRANSFER_FROM_CLIENT_RESULT:
                    mess = to_string(FILE_TRANSFER_FROM_CLIENT) + "|" + u.username + "|" + get_filename(buff) + "|" +
                           request::get_last(buff);
//                    cout << "send content file " << get_filename(buff) << request::get_last(buff) << request::get_username(buff) << endl;
                    a = list_users.begin();
                    for (a; a != list_users.end(); a++) {
                        if (strcmp(a->username.c_str(), request::get_username(buff)) == 0) {
//                            cout << "send content get file " << get_filename(buff) << request::get_last(buff) << endl;
                            send(a->client_transfer_sock, mess.c_str(), strlen(mess.c_str()), 0);
                            break;
                        }
                    }
                    break;

            }
        }

    }
}

char *transfer::get_filename(char *buff) {
    int n = 0, k = 0, j = 0;
    char *s;
    s = (char *) malloc(sizeof(char) * 100);
    for (n = strlen(buff); n > 0; n--) {
        if (buff[n] == '|') {
            k++;
            if (k == 2) break;
        }
    }

    for (int i = n + 1; buff[i] != '|'; ++i) {
        s[j++] = buff[i];
    }

    s[j] = '\0';
    return s;
}

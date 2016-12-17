//
// Created by lengkeng on 06/12/2016.
//
#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <zconf.h>
#include "signup_login.h"
#include "../../libs/entity/user.h"
#include "../data/list_users.h"
#include "../request/request.h"

using namespace std;

void *signup_login::signup_login_thread(void *us) {
//    init
    list<user>::iterator a = list_users.begin();
    for (a; a != list_users.end(); a++) {
        printf("%s ", a->username.c_str());
    }
    printf("\n");
//    cout << list_users.size() << endl;
    user u = *(user *) us;
    cout << "Thread " << u.client_sock << endl;
    string welcome_message = "Welcome to my server!";
    int bytes_sent, bytes_recv;
    char buff[1024];
    u.status = 0;
//    send welcome
    send(u.client_sock, welcome_message.c_str(), strlen(welcome_message.c_str()), 0);

    while (u.status == AUTH_FAILURE) {
        cout << "Waiting... " << u.client_sock << endl;
        bytes_recv = (int) recv(u.client_sock, buff, 1024, 0);
        buff[bytes_recv] = '\0';
        if (bytes_recv == 0) {
            cout << u.client_sock << " was disconnected" << endl;
            close(u.client_sock);
            list<user>::iterator a = list_users.begin();
            for (a; a != list_users.end(); a++) {
                if (a->client_sock == u.client_sock) {
                    a->status = 0;
                    a->username = "";
                }
            }
            pthread_exit(NULL);
        }
        switch (get_status_code(buff)) {
            case SIGN_UP:
                if (signup_login::check_username_exist(buff)) {
                    string error = to_string(SIGN_UP_USER_EXIST) + "| Username has been taken";
                    cout << get_username(buff) << " => " << error << endl;
                    send(u.client_sock, error.c_str(), strlen(error.c_str()), 0);
                } else {
                    signup_login::create_user(buff);
                    string success = to_string(SIGN_UP_USER_CREATED) + "| Username has been created";
                    cout << get_username(buff) << " => " << success << endl;
                    send(u.client_sock, success.c_str(), strlen(success.c_str()), 0);
                }
                break;
            case SIGN_IN:

                if (signup_login::check_login(buff)) {
                    if (signup_login::check_logged(buff)) {
                        u.username = get_username(buff);
                        string success = to_string(SIGN_IN_SUCCESS) + "| Login success";
                        cout << get_username(buff) << " => " << success << endl;
                        send(u.client_sock, success.c_str(), strlen(success.c_str()), 0);
                        u.status = AUTH_SUCCESS;

                        list<user>::iterator a = list_users.begin();
                        for (a; a != list_users.end(); a++) {
                            if (a->client_sock == u.client_sock) {
                                a->username = get_username(buff);
                                a->status = AUTH_SUCCESS;
                                u = *a;
                                break;
                            }
                        }
                        request::file_request(u);
                    } else {
                        string error = to_string(SIGN_IN_EXIST) + "| Account already logged!";
                        cout << get_username(buff) << " => " << error << endl;
                        send(u.client_sock, error.c_str(), strlen(error.c_str()), 0);
                    }
                } else {
                    string error = to_string(SIGN_IN_FAILURE) + "| Invalid username/password";
                    cout << get_username(buff) << " => " << error << endl;
                    send(u.client_sock, error.c_str(), strlen(error.c_str()), 0);
                }
                break;
        }
    }
}

char *signup_login::get_username(char buff[]) {
    char *s;
    s = (char *) malloc(sizeof(char) * 100);
    int j = 0;
    if (get_status_code(buff) == SIGN_UP || get_status_code(buff) == SIGN_IN) {
        for (int i = 4; i < strlen(buff); i++) {
            if (buff[i] != '|' && buff[i] != '\0') {
                s[j++] = buff[i];
            } else {
                s[j] = '\0';
                return s;
            }
        }
    }
    return s;
}

char *signup_login::get_password(char *buff) {
    int n = 0, j = 0;
    char *s;
    s = (char *) malloc(sizeof(char) * 100);
    if (get_status_code(buff) == SIGN_UP || get_status_code(buff) == SIGN_IN) {
        for (n = strlen(buff); buff[n] != '|'; n--);
        for (int i = n + 1; i < strlen(buff); i++) {
            s[j++] = buff[i];
        }
        s[j] = '\0';
        return s;

    }


}

bool signup_login::check_username_exist(char buff[]) {
    FILE *f;
    char u[100], p[100];
    f = fopen(DATA_FILE, "r+");
    if (f == NULL) return false;
    while (!feof(f)) {
        fscanf(f, "%s %s\n", u, p);
        if (strcmp(u, get_username(buff)) == 0) {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}

bool signup_login::create_user(char *buff) {
    FILE *f;
    f = fopen(DATA_FILE, "a");
    if (f == NULL) return false;
    cout << get_username(buff) << "|" << get_password(buff) << endl;
    fprintf(f, "%s %s\n", get_username(buff), get_password(buff));
    fclose(f);
    return true;
}

bool signup_login::check_login(char *buff) {
    FILE *f;
    char u[100], p[100];
    f = fopen(DATA_FILE, "r+");
    if (f == NULL) return false;
    while (!feof(f)) {
        fscanf(f, "%s %s\n", u, p);
//        cout << u << "|" << p << "|" << get_username(buff) << endl;
        if (strcmp(u, get_username(buff)) == 0) {
            if (strcmp(p, get_password(buff)) == 0) {
                fclose(f);
                return true;
            } else {
                fclose(f);
                return false;
            }
        }
    }
    fclose(f);
    return false;
}

bool signup_login::check_logged(char *buff) {
    list<user>::iterator a = list_users.begin();
    for (a; a != list_users.end(); a++) {
        if (a->status == AUTH_SUCCESS) {
            if (strcmp(get_username(buff), a->username.c_str()) == 0)
                return false;
        }
    }
    return true;
}

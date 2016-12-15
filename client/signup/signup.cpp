//
// Created by quangminh on 24/11/2016.
//
#include <iostream>
#include <sys/socket.h>
#include <sstream>
#include "signup.h"
#include "../../libs/functions/string_helper.h"

int signup::sign( int client_sock) {
    string username;
    string password,passwordConfirm;
    string protocolCall;
    char buff[1024];
    stringstream convert;
    convert<<SIGN_UP;
    protocolCall+=convert.str();

    printf("Insert username\n");
    cin >> username;
    protocolCall+="|"+username;
    printf("Insert password\n");
    cin >> password;
    printf("Insert password confirm\n");
    cin>>passwordConfirm;
    if(strcmp(password.c_str(),passwordConfirm.c_str())==0){
        protocolCall+="|"+password;
        int bytes_sent = send(client_sock, protocolCall.c_str(), protocolCall.length(), 0); /* send to the client welcome message */
        int bytes_received = recv(client_sock, buff, 1024, 0);
        buff[bytes_received]='\0';
        string_helper::readState(buff);
        cout<<buff<<endl;
    }
    else{
    }
}

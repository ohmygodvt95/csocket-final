//
// Created by quangminh on 29/11/2016.
//

#include <cstring>
#include <list>
#include <zconf.h>
#include "find_file.h"
#include "../../libs/constants.h"
#include "../../libs/functions/string_helper.h"
#include "../share.h"

void find_file::findFileWithKeyword(int client_sock,int client_transfer_sock) {
    char *p;
    total = 5;
    int state, numberRequest;
    string fileName;
    string listUserHaveFile[20];
    string protocolCall, responseCall;
    char *buff;
    cout << "Insert file name: " << endl;
    cin >> fileName;
    //cout << fileName << endl;
    fileNameRequest = fileName;
    stringstream convert, convert2;
    convert << FIND_FILE_REQUEST_TO_SERVER;
    protocolCall = convert.str();
    protocolCall += "|" + fileName;

    int bytes_sent = send(client_sock, protocolCall.c_str(), protocolCall.length(), 0);
    //cout<<protocolCall<<endl;
    total = -1;
    totalUserHasFile = 0;
    while (total != 0);
    if (totalUserHasFile != 0) {

        cout << "Enter username want to get file: " << endl;
        cout << "0. Cancel " << endl;
        string username;
        cin >> username;
        userHasFile=username;
        FILE *f;
        string path=ROOT+fileNameRequest+"_"+username;

        f=fopen(path.c_str(),"w+");
        fclose(f);
        pivot = 0;
        string mess = to_string(SELECT_FILE_FROM_CLIENT) + "|" + username + "|" + fileNameRequest + "|" + to_string(pivot);
        cout << "=> Waiting transfer file.. " << fileNameRequest << " form " << username <<endl;
        send(client_transfer_sock, mess.c_str(), mess.length(), 0);

//        cout << mess << endl;
    } else {
        cout << "File not found!" << endl;
    }


}

bool find_file::checkExistFile(char *fileName) {
    FILE *f;
    string root =  ROOT;
    root += fileName;
    f = fopen(root.c_str(), "r");
    //cout<< fileName <<endl;
    if (f == NULL) {
//        cout << "khng tim thay file " << endl;
        return false;
    } else {
        fclose(f);
        return true;
    }

    return nullptr;
}

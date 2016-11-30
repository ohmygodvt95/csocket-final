//
// Created by quangminh on 29/11/2016.
//

#include "find_file.h"
#include "../../libs/constants.h"

void find_file::findFileWithKeyword(int client_sock) {

    string fileName;
    string protocolCall;

    cout<<"Insert file name"<<endl;
    cin>>fileName;
    stringstream convert;
    convert<<FIND_FILE_REQUEST_TO_SERVER;
    protocolCall=convert.str();
    protocolCall+=","+fileName;
    int bytes_sent = send(client_sock, protocolCall.c_str(), protocolCall.length(), 0); /* send to the client welcome message */

}

char *find_file::checkExistFile(char *fileName) {
    return nullptr;
}

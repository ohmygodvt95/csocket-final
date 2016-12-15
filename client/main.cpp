//

#include "main.h"
#include "signin/signin.h"
#include "find_file/find_file.h"
#include "signup/signup.h"
//
//

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <zconf.h>
#include <thread>
#include <pthread.h>

#define SIGN_SUCCESS "success"
#define SIGN_FAILURE "failure"
#define SIGN_LOCKED "locked"
#define IP_TO_SERVER "192.168.100.15"
using namespace std;
user curUser = user();
int total = 0;

int totalUserHasFile = 0;

int pivot = 0;

string fileNameRequest;
string userHasFile;
int readState(char c[]) {
    int state;
    char *p;
    p = strtok(c, "|");
    return atoi(p);
}

char *readKeyword(char c[]) {
    char *p;
    p = strtok(c, "|");
    p = strtok(NULL, "|");
    p = strtok(NULL, "|");
    return p;

}


char *readUserSend(char c[]) {
    char *p;
    p = strtok(c, "|");
    p = strtok(NULL, "|");
    return p;

}

int readTotal(char c[]) {
    char *p;
    p = strtok(c, "|");
    p = strtok(NULL, "|");
    return atoi(p);
}
int readPivot(char c[]){
    char *p;
    p=strtok(c,"|");
    p = strtok(NULL, "|");
    p = strtok(NULL, "|");
    p = strtok(NULL, "|");
    return  atoi(p);


}
char *readData(char c[]) {
    char *p;
    p = strtok(c, "|");
    p = strtok(NULL, "|");
    p = strtok(NULL, "|");
    p = strtok(NULL, "|");

    return p;
}

void printfUsernameHasFile(char c[]) {
    char *p;
    p = strtok(c, "|");
    p = strtok(NULL, "|");
    string username = p;
    int state;
    p = strtok(NULL, "|");
    state = atoi(p);
    if (state == 1) {
        printf("%d. %s\n", totalUserHasFile + 1, username.c_str());
        totalUserHasFile++;
    }

}

void *listenRequestFindFileFromServer(void *clientsock_id) {
    long clientsock;
    clientsock = (long) clientsock_id;
    int bytes_received, bytes_send;

    while (true) {
        char buff[1024];
        char buff2[1024];
        char buff3[1024];
        char buff4[1024];

        string protocolCall;
        bytes_received = recv(clientsock, buff, 1024, 0);
        buff[bytes_received] = '\0';
        // cout<< buff <<endl;
        strcpy(buff2, buff);
        strcpy(buff3, buff);
        strcpy(buff4, buff);

        if (bytes_received == 0) {
            continue;
        }

        switch (readState(buff)) {
            case FIND_FILE_REQUEST_TO_CLIENT:
                protocolCall = to_string(FIND_FILE_RESPONSE_FROM_CLIENT) + "|" + readUserSend(buff2);
                if (find_file::checkExistFile(readKeyword(buff3)) == 1) {
                    protocolCall += "|1";
                } else {
                    protocolCall += "|0";
                }
                send(clientsock, protocolCall.c_str(), protocolCall.length(), 0);
//                cout << protocolCall << endl;
                break;
            case FIND_FILE_INFOR:
                total = readTotal(buff2);
                //  cout << "total request :"<<total <<endl;

                break;
            case FIND_FILE_RESPONE_TO_CLIENT:
                cout << buff2 << endl;
                printfUsernameHasFile(buff2);
                total--;
                //  cout << total <<endl;
                break;

        }
    }

}



void *openThreadForTransferFile(void *clientsockSendFile_id) {
    long clientsock;

    clientsock = (long) clientsockSendFile_id;
    while (true) {
        pthread_t pthreadSendToUser;
        char buff[2048];
        char buff2[2048];
        char buff3[2048];
        char buff4[2048];


        int bytes_received = recv(clientsock, buff, 2048, 0);
        buff[bytes_received] = '\0';
        if (bytes_received == 0) {
            continue;
        }
        strcpy(buff2, buff);
        strcpy(buff3, buff);
        strcpy(buff4, buff);
        FILE *f;
        string keyword;
        string usersend;
        int pivot;
        string path;
        int size;
        string mess;
        int a = readState(buff);
        switch (a) {
            case FILE_TRANSFER_TO_CLIENT:
                usersend=readUserSend(buff2);
                keyword=readKeyword(buff3);
                path+=ROOT+keyword;
                pivot=readPivot(buff4);
                f=fopen(path.c_str(),"r");

                fseek(f,pivot,0);
                size=fread(buff,1,1024,f);
                buff[size]='\0';
                mess=to_string(FILE_TRANSFER_FROM_CLIENT_RESULT)+"|"+usersend+"|"+keyword+"|"+buff;
                size=send(curUser.clientTranferSock,mess.c_str(),mess.length(),0);
//                cout << size << endl;

                break;


            case FILE_TRANSFER_FROM_CLIENT:
                FILE *f;
                keyword=readKeyword(buff2);

                string data=readData(buff3);

                path+=ROOT+keyword+"_"+userHasFile;
                f=fopen(path.c_str(),"a+");
                fprintf(f, "%s", data.c_str());
                fclose(f);
                if(data.length()==1024){
                    pivot+=1024;
                    string mess = to_string(SELECT_FILE_FROM_CLIENT) + "|" + userHasFile + "|" + keyword + "|" + to_string(pivot);
                    send(curUser.clientTranferSock, mess.c_str(), mess.length(), 0);

                } else if(data.length()<1024){
                    pivot=0;
                    cout << "=> File traansfer successful"<<endl;
                }
                break;



        }


    }

}


int main() {
    int client_sock, client_transfer_sock;
    char buff[1024];
    FILE *f;
    pthread_t checkFileThread, openTranferThread;
    struct sockaddr_in server_addr;
    struct sockaddr_in server_addr2;

    int bytes_sent, bytes_received;
    int stage = 0;

    client_sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5500);
    server_addr.sin_addr.s_addr = inet_addr(IP_TO_SERVER);
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

    cout << buff << endl;

    char c, ch;
    c = '0';
    int state = 0;
    do {
        if (state < 10) {
            printf("SHARE FILE SERVICE\n----------------------------------\n");
            printf("1: Sign In\n2: Sign Up\nq: Quit\n");
            do {
                printf("You choice?: ");
                cin >> c;
                state = state * 10 + (c - '0');

            } while (c != '1' && c != '2' && c != 'q');
            switch (c) {
                case '1':
                    //signin::showView();
                    curUser = signin::sign_in(&state, client_sock);
                    if (state != 0) {
                        client_transfer_sock = socket(AF_INET, SOCK_STREAM, 0);
                        server_addr2.sin_family = AF_INET;
                        server_addr2.sin_port = htons(5000);
                        server_addr2.sin_addr.s_addr = inet_addr(IP_TO_SERVER);

                        if (connect(client_transfer_sock, (struct sockaddr *) &server_addr2, sizeof(struct sockaddr)) !=
                            0) {
                            printf("\nError!Can not connect to sever!Client exit imediately! ");
                            return 0;
                        }

                        bytes_received = recv(client_transfer_sock, buff, 1024, 0);

                        buff[bytes_received] = '\0';

                        cout << buff << endl;

                        send(client_transfer_sock, curUser.username.c_str(), curUser.username.length(), 0);

                        curUser.clientTranferSock = client_transfer_sock;
                        pthread_create(&checkFileThread, NULL, listenRequestFindFileFromServer, (void *) client_sock);
                        pthread_create(&openTranferThread, NULL, openThreadForTransferFile,
                                       (void *) client_transfer_sock);

                    }
                    break;
                case '2':
                    signup::sign(client_sock);
                    break;
                case 'q':
                    state = -1;
                    break;
            }
        } else if (state >= 10) {
            printf("Welcome To ShareFile App\n----------------------------\n");
            printf("1: Find file\nq: Logout\n");
            do {
                printf("You choice?: ");
                cin >> ch;
                state = state * 10 + (ch - '0');

            } while (ch != '1' && ch != 'q');
            switch (ch) {
                case '1':
                    find_file::findFileWithKeyword(client_sock, client_transfer_sock);
                    break;
                case 'q':
                    state = -1;
                    break;
            }
        }
    } while (state != -1);


    return 0;
}

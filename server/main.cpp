#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <zconf.h>
#include <string.h>
#include <wait.h>
#include <list>
#include <sstream>
#include "../libs/entity/user.h"
#include "../libs/constants.h"
using namespace std;
#define PORT 5500   /* Port that will be opened */
#define BACKLOG 20   /* Number of allowed connections */

void sig_chld(int signo){
    pid_t pid;
    int stat;
    while((pid=waitpid(-1,&stat,WNOHANG))>0)
        printf("[ForkingServer] Child %d terminated\n",pid);
}

user fromStringToUser(char c[]) {
    user u;
    int len;
    len=strlen(c);
    c[len-1]='\0';
    char *p;
    p = strtok(c, ",");
    u.username = p;
    p = strtok(NULL, ",");
    u.password = p;
    u.status=0;

    return u;
}
int readState(char c[]){
    int state;
    char *p;
    p=strtok(c, ",");
    return atoi(p);
}
list<user> readFile(FILE *in){
    list<user> list;
    user u=user();
    char c[80];
    while(fgets(c,80,in)!=NULL)
    {
        list.push_back(fromStringToUser(c));

    }

    return list;
}
int check_user_password(char str[],list<user> listUser,int clientSock) {
    cout<< str <<endl;

    char *p;
    string username;
    string password;
    //get status code
    p = strtok(str, ",");
    //get username
    p=strtok(NULL,",");
    username=p;
    //get password
    p=strtok(NULL,",");
    cout<<username<<endl;
    list<user>::iterator a =listUser.begin();
    for(a;a!=listUser.end();a++){
        if(strcmp(username.c_str(),a->username.c_str())==0 && strcmp(password.c_str(),a->password.c_str())==0 ){
            a->status=1;
            a->clientSock=clientSock;
            cout<< "ok" <<endl;
            return 200;
        }
    password = p;


    }
    cout<< "failed" <<endl;

    return 404;
}


int main() {
    pid_t pid;

    int listen_sock, conn_sock; /* file descriptors */
    char recv_data[1024];
    int bytes_sent, bytes_received;
    struct sockaddr_in server; /* server's address information */
    struct sockaddr_in client; /* client's address information */
    FILE *in;
    in = fopen("/home/quangminh/NetWork Programming/csocket-final/server/db.txt", "r+");
    list<user> listUser = readFile(in);
    int sin_size;

    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  /* calls socket() */
        printf("socket() error\n");
        exit(-1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
    server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */
    bzero(&(server.sin_zero), 8); /* zero the rest of the structure */


    if (bind(listen_sock, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) { /* calls bind() */
        printf("bind() error\n");
        exit(-1);
    }

    if (listen(listen_sock, BACKLOG) == -1) {  /* calls listen() */
        printf("listen() error\n");
        exit(-1);
    }
    cout <<"hello"<< endl;
    while (1) {
        string data_param;
        stringstream convert;
        user u=user();
        string response;
        int boo;
        sin_size = sizeof(struct sockaddr_in);
        if ((conn_sock = accept(listen_sock, (struct sockaddr *) &client, (socklen_t *) &sin_size)) ==
            -1) { /* calls accept() */
            printf("accept() error\n");
            exit(-1);
        }

        if ((pid = fork()) == 0) {
            close(listen_sock);
            int state;

            printf("You got a connection from %s\n", inet_ntoa(client.sin_addr)); /* prints client's IP */
            bytes_sent = send(conn_sock, "Welcome to my server.\n", 22, 0); /* send to the client welcome message */
            if (bytes_sent < 0) {
                printf("\nError!Can not sent data to client!");
                close(conn_sock);
                continue;
            }
            bytes_received = recv(conn_sock, recv_data, 1024, 0);
            recv_data[bytes_received] = '\0';
            data_param=recv_data;
            state = readState(recv_data);
            printf("%s\n",data_param.c_str());
            printf("%d\n",state);
            while (true) {
                switch (state) {
                    case SIGN_IN:
                        
                        convert << check_user_password((char *) data_param.c_str(), listUser, conn_sock);
                        response = convert.str();
                        cout << response << endl;
                        bytes_sent = send(conn_sock, "200", 4, 0);

                        break;
                    case SIGN_UP:
                        break;
                    case FIND_FILE_REQUEST_TO_SERVER:
                        bytes_sent=send(conn_sock,"204,quangminh,vinhthien",27,0);

                        break;
                }

            }
            exit(0);
        }


        signal(SIGCHLD, sig_chld);

        close(conn_sock);
    }

    close(listen_sock);
    return 0;


}
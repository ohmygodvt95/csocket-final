#include <pthread.h>
#include <stdio.h>
#include <zconf.h>

/* This is our thread function.  It is like main(), but for a thread*/
void *threadFunc(void *arg) {
    char *str;
    int i = 0;

    str = (char *) arg;

    while (true) {
        usleep(1);
        printf("threadFunc says: %s\n", str);
        scanf("%d", &i);
        ++i;
    }

    return NULL;
}

int main(void) {
    pthread_t pth;    // this is our thread identifier
    int i = 0;

    pthread_create(&pth, NULL, threadFunc, (void *) "foo");

    while (true) {
        usleep(1000);
        printf("main is running...\n");
        ++i;
    }

//    printf("main waiting for thread to terminate...\n");
//    pthread_join(pth,NULL);

    return 0;
}
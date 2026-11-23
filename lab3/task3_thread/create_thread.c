#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function(void *threadid) {
    long tid = (long)threadid;
    printf("Thread #%ld is running\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int rc;
    long t;
    for (t = 0; t < 2; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_message_function, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

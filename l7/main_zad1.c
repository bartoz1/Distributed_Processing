#include <stdio.h>
#include <pthread.h>

void *f(void *i) {
    printf("Thread says: Hello! \n");
    return NULL;
}

int main() {
    pthread_t w[4];
    for(size_t i=0 ;i<4; i++) {
        pthread_create(&w[i], NULL, f, NULL);
        pthread_join(w[i], NULL);
    }

    printf("HEllo world from main thread!\n");
    return 0;
}
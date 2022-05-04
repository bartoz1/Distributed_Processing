#include <stdio.h>
#include <pthread.h>

#define N 1000
int array[N];

struct task_data {
    int start;
    int end;
};

void useSitoErastotelesa(int start, int end) {

    for (int i=2; i<end; i++) {
        for (int j=start ;j<=end; j++) {
            if (i != array[j]  && array[j] % i== 0)
                array[j] = 0;
        }
    }
}

void *f(void *i) {
    printf("thread started\n");
    //printf("Thread says: Hello! \n");
    struct task_data* data = (struct task_data*) i;
    useSitoErastotelesa(data->start, data->end);

    printf("thread finished\n");
    return NULL;
}

int main() {

    for(size_t i=0; i<N-1; i++) {
        array[i] = i+2;
    }

    pthread_t w[4];
    struct task_data dane[4] = {{0, 249},{250, 499},{500, 749},{750, 1000}};

    for(size_t i=0 ;i<4; i++) {
        pthread_create(&w[i], NULL, f, (void*)&dane[i]);
        //pthread_join(w[i], NULL);
    }
    for(size_t i=0 ;i<4; i++) {
        //pthread_create(&w[i], NULL, f, (void*)&dane[i]);
        pthread_join(w[i], NULL);
    }
    for(int i=0; i<N; i++)
        if (array[i] != 0)
            printf("%d ", array[i]);
    //printf("HEllo world from main thread!\n");
    return 0;
}
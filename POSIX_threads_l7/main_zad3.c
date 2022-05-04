#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define N 1000
int array[N];

struct task_data {
    int start;
    int end;
};

int primes[N];
int primes_count = 0;
pthread_mutex_t lock;

int isPrime(int number) {
    if (number <= 1)
        return 0;
    int is = 1;
    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) {
            is = 0;
            break;
        }
    }
    return is;
}

void findPrimes(int start, int end) {

    for (int j=start ;j<end; j++) {
        if (isPrime(array[j]) == 1) {
            pthread_mutex_lock(&lock);
            primes[primes_count++] = array[j];
            pthread_mutex_unlock(&lock);
        } else
            array[j] = 0;
    }

}

void *f(void *i) {
    printf("thread started\n");
    //printf("Thread says: Hello! \n");
    struct task_data* data = (struct task_data*) i;
    findPrimes(data->start, data->end);

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
    for(int i=0; i<primes_count; i++)
        printf("%d ", primes[i]);
    printf("\n");
    //printf("HEllo world from main thread!\n");
    return 0;
}
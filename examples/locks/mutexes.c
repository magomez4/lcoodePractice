#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* thread_func(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Thread %d is in the critical section.\n", *(int*)arg);
    sleep(1);
    printf("Thread %d is leaving the critical section.\n", *(int*)arg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}

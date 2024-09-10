#include <stdio.h>
#include <pthread.h>

pthread_rwlock_t rwlock;

void* read_func(void* arg) {
    pthread_rwlock_rdlock(&rwlock);
    printf("Thread %d is reading.\n", *(int*)arg);
    // Simulate read
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void* write_func(void* arg) {
    pthread_rwlock_wrlock(&rwlock);
    printf("Thread %d is writing.\n", *(int*)arg);
    // Simulate write
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main() {
    pthread_t threads[4];
    int thread_ids[4] = {1, 2, 3, 4};

    pthread_rwlock_init(&rwlock, NULL);

    pthread_create(&threads[0], NULL, read_func, &thread_ids[0]);
    pthread_create(&threads[1], NULL, read_func, &thread_ids[1]);
    pthread_create(&threads[2], NULL, write_func, &thread_ids[2]);
    pthread_create(&threads[3], NULL, read_func, &thread_ids[3]);

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);
    return 0;
}

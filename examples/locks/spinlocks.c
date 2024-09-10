#include <stdio.h>
#include <pthread.h>

pthread_spinlock_t spinlock;

void* thread_func(void* arg) {
    pthread_spin_lock(&spinlock);
    printf("Thread %d is in the critical section.\n", *(int*)arg);
    // Simulate work
    pthread_spin_unlock(&spinlock);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};

    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_spin_destroy(&spinlock);
    return 0;
}

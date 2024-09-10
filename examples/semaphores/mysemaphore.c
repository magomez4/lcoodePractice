#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void* thread_func(void* arg) {
	for(int i = 0; i < 3; i++)
	{
		sem_wait(&semaphore);
		printf("Thread %d is in the critical section.\n", *(int*)arg);
		sleep(1);
		printf("Thread %d is leaving the critical section.\n", *(int*)arg);
		sem_post(&semaphore);
		sleep(1);
	}
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};

    sem_init(&semaphore, 0, 1);

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);
    return 0;
}

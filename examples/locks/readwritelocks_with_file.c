#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;  // Read-Write lock
FILE *file;               // Shared file pointer

void* read_func(void* arg) {
    int thread_id = *(int*)arg;

    // Acquire the read lock
    pthread_rwlock_rdlock(&rwlock);

    // Read from the file
    printf("Thread %d is reading from the file:\n", thread_id);
    char buffer[256];
    fseek(file, 0, SEEK_SET);  // Go to the beginning of the file
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("Thread %d read: %s", thread_id, buffer);
    }
    printf("\n");

    // Release the read lock
    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

void* write_func(void* arg) {
    int thread_id = *(int*)arg;

    // Acquire the write lock
    pthread_rwlock_wrlock(&rwlock);

    // Write to the file
    printf("Thread %d is writing to the file.\n", thread_id);
    fseek(file, 0, SEEK_END);  // Go to the end of the file
    fprintf(file, "Thread %d was here.\n", thread_id);
    fflush(file);  // Ensure the write is flushed to the file

    // Release the write lock
    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_ids[5] = {1, 2, 3, 4, 5};

    // Initialize the read-write lock
    pthread_rwlock_init(&rwlock, NULL);

    // Open the shared file
    file = fopen("shared_file.txt", "w+");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Create threads (some for reading and some for writing)
    pthread_create(&threads[0], NULL, read_func, &thread_ids[0]);
    pthread_create(&threads[1], NULL, write_func, &thread_ids[1]);
    pthread_create(&threads[2], NULL, read_func, &thread_ids[2]);
    pthread_create(&threads[3], NULL, write_func, &thread_ids[3]);
    pthread_create(&threads[4], NULL, read_func, &thread_ids[4]);

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    fclose(file);
    pthread_rwlock_destroy(&rwlock);

    return 0;
}

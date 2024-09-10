/*Multi-threaded Counter with Synchronization*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>

#define MAXTHREADS 4
#define MAXOPS 4
int counter = 0;
pthread_mutex_t mutex;
sem_t writerSemaphore;
sem_t readerSemaphore;


typedef struct
{
	bool isWriterThread;
	
} mutexInfo;

// allocate mutexholder info
mutexInfo mutexHolderInfo;

void increaseCounter()
{
	counter++;
}

void printCounter(unsigned long threadID)
{
	printf("Thread ID: %lu\n", threadID);	
	printf("counter = %d\n", counter);	
}

void* readerThreadRoutine(void* args)
{
	pthread_t myThreadID = pthread_self();
	//for(int i = 0; i < MAXOPS; i++)
	//{
		// START OF the critical section 
			// wait until a writer thread is holding the mutex
			//while(!mutexHolderInfo.isWriterThread)
			//{
				//// wait until variable changes before
				//// you request the mutex
			//}
			sem_wait(&readerSemaphore); // wait until there is something to read
			// acquire mutex lock
			pthread_mutex_lock(&mutex);
			// signal that you are a reader
			mutexHolderInfo.isWriterThread = false;
			
			printCounter((unsigned long)myThreadID);
			
			// release lock
			pthread_mutex_unlock(&mutex);
			
		// END OF the critical section 
	//}
	return NULL;
}

void* writerThreadRoutine(void* args)
{
	pthread_t myThreadID = pthread_self();
	//for(int i = 0; i < MAXOPS; i++)
	//{
		// START OF the critical section 
			// wait until a non-writer thread is holding the mutex
			//while(mutexHolderInfo.isWriterThread)
			//{
				//// wait until variable changes before
				//// you request the mutex
			//}

			sem_wait(&writerSemaphore); // lower the counter of the semaphore

			// acquire mutex lock
			pthread_mutex_lock(&mutex);
			// signal that you are a writer thread
			mutexHolderInfo.isWriterThread = true;
			
			printf("Thread ID: %lu increasing counter...\n", (unsigned long) myThreadID);
			increaseCounter();
			
			// release lock
			//mutexHolderInfo.isWriterThread = false;
			pthread_mutex_unlock(&mutex);
			
			sem_post(&readerSemaphore); // tell the readers that you have written something
			sem_post(&writerSemaphore); // increase the semaphore so others can write
		// END OF the critical section 
	//}
	return NULL;
}

int main ()
{
	//OBJECTIVES:
	// Create multiple threads (e.g., 5) that will increment a shared counter.
	// initialize semaphore so that 2 threads write before anyone reads
	// Use a mutex to protect access to the shared counter.
	// Use a semaphore to limit the number of threads that can increment the counter at the same time (e.g., limit to 2 threads).
	
	pthread_t thread[MAXTHREADS]; // declare the threads
	
	// 0 = semaphore access within threads of same process, 2 = max 2 threads allowed
	sem_init(&writerSemaphore, 0, 2); 
	// 0 = semaphore access within threads of same process, 0 = no threads allowed until semaphore changes
	sem_init(&readerSemaphore, 0, 0);


	// launch the threads
	//pthread_create(&myNewThread, NULL, threadRoutine, NULL); //single extra thread would look like this
	bool writer = true;
	mutexHolderInfo.isWriterThread = false; // start by allowing a writer to increase counter
	void* (*threadRoutine)(void*);
	for( int i = 0; i < MAXTHREADS; i++)
	{
		if(writer)
		{
			threadRoutine = writerThreadRoutine;
		}
		else
		{
			threadRoutine = readerThreadRoutine;
		}
		pthread_create(&thread[i], NULL, threadRoutine, NULL);
		writer = !writer;
	}
	
	
	// join the threads to finish the program
	for( int i = 0; i < MAXTHREADS; i++)
	{
		pthread_join(thread[i], NULL);
	}
	
	sem_destroy(&writerSemaphore);
	sem_destroy(&readerSemaphore);
	pthread_mutex_destroy(&mutex);

	return 0;
}

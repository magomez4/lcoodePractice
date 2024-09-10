#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define INITIALHEAPSIZE 100

typedef struct minHeap{
    long int* heap;
    int size;
    int capacity;
    // leftChild of i = 2i+1
    // leftChild of i = 2i+2
    // parent of i = floor((i-1)/2)
}minHeap;

minHeap* createHeap()
{
    minHeap* newHeap = (minHeap*)malloc(sizeof(minHeap));
    if(newHeap == NULL)
    {
        printf("BAD ALLOCATION\n");
        exit(1);
    }
    newHeap->heap = (long int*)malloc(INITIALHEAPSIZE*sizeof(long int));
    if(newHeap->heap == NULL)
    {
        printf("BAD ALLOCATION\n");
        free(newHeap);
        exit(1);
    }
    newHeap->size = 0;
    newHeap->capacity = INITIALHEAPSIZE;
    return newHeap;
}

void swap(minHeap* obj, int a, int b)
{
    long int temp = obj->heap[a];
    obj->heap[a] = obj->heap[b];
    obj->heap[b] = temp;
}

// void heapifyUp(minHeap* obj)
// {
//     // something got added to the end.
//     // make sure it fits there,
//     // for a min-heap, every child
//     //  needs to be >= its parent, so
//     // i need to loop until "i" becomes root or
//     // until the object at "i" is >= to its parent
//     int i = obj->size - 1; // last index of heap
//     while(i > 0)
//     {
//         int parentIdx = floor((i-1)/2);
//         swap(obj, i, parentIdx);
//         i = parentIdx;
//     }
// }

void heapifyUp(minHeap* obj) {
    // something got added to the end.
    // make sure it fits there,
    // for a min-heap, every child
    //  needs to be >= its parent, so
    // i need to loop until "i" becomes root or
    // until the object at "i" is >= to its parent
    int i = obj->size - 1;
    int parentIdx = (i - 1) / 2;
    while(i > 0 && obj->heap[i] < obj->heap[parentIdx]) {
        swap(obj, i, parentIdx);
        i = parentIdx;
        parentIdx = (i - 1) / 2;
    }
}

void heapifyDown(minHeap* obj, int idx)
{
    // something gor removed and replaced
    // by the last element in heap, now
    // re-order from idx down. In a
    // min-heap we always replace "i"
    // with the smallest of its two children 
    
    int i = idx;
    int leftChild = (2*i)+1;    
    int rightChild = (2*i)+2;
    // I only check leftchild because if the
    // left child would be over the size limit,
    // then there is definitely no right child
    while(leftChild < obj->size) 
    {
        int smallestChild = leftChild;
        // if there is a left child, there might
        // be a right child, so we check for that
        if(rightChild < obj->size)
        {
            if(obj->heap[rightChild] < obj->heap[leftChild])
            {
                smallestChild = rightChild;
            }
        }
        if(obj->heap[smallestChild] < obj->heap[i])
        {
            swap(obj, smallestChild, i);
            i = smallestChild;
            leftChild = (2*i)+1;    
            rightChild = (2*i)+2;
        }
        else 
        {
            // the heap order is correct, so
            // we can stop the heapify
            break;
        }
    }
}
void ensureHeapCapacity(minHeap* obj, int newSize)
{
    if(obj->capacity <= newSize)
    {
        // duplicate capacity of heap
        obj->heap = (long int*)realloc(obj->heap, (2*obj->capacity)*sizeof(long int));
        if(obj->heap == NULL)
        {
            printf("BAD ALLOCATION\n");
            free(obj);
            exit(1);
        }        
        obj->capacity = 2*(obj->capacity);
    }
}
void addToHeap(minHeap* obj, long int val)
{
    ensureHeapCapacity(obj, obj->size + 1);
    obj->size++;
    obj->heap[obj->size - 1] = val;
    heapifyUp(obj);
}

long int findInHeap(minHeap* obj, long int val)
{
    for(int i = 0; i < obj->size; i++)
    {
        if(obj->heap[i] == val)
        {
            return i;
        }
    }
    return -1; //not found
}

void removeFromHeap(minHeap* obj, long int val)
{
    int idx = findInHeap(obj, val);
    if(idx != -1)
    {
        obj->heap[idx] = obj->heap[obj->size - 1];
        obj->size--;
        heapifyDown(obj, idx);
    }
}

void freeHeap(minHeap* obj)
{
    free(obj->heap);
    free(obj);
}


int main() {

    // get number of queries
    char* string = NULL;
    int bufferSize = 0;
    int readSize;
    // printf("creating heap...\n");
    minHeap* myHeap = createHeap();
    // get number of queries
    // printf("reading num inputs...\n");
    readSize = getline(&string, &bufferSize, stdin);
    // printf("readsize = %zd, bufferSize = %zd\n", readSize, bufferSize);
    int numQueries = atoi(string);
    // printf("numQueries = %d\n", numQueries);
    
    while(numQueries > 0)
    {
        free(string);
        string = NULL;
        bufferSize = 0;
        readSize = getline(&string, &bufferSize, stdin);
        char* endPointer = NULL;
        int function = strtol(string, &endPointer, 10);
        // long int argument = strtol(endPointer, &endPointer, 10);
        long int argument = strtol(endPointer, &endPointer, 10);
        // printf("function: %ld, argument: %ld \n", function, argument);
        if(function == 1)
        {
            // printf("adding to heap\n");
            addToHeap(myHeap, argument);
        }
        else if( function == 2)
        {
            // printf("removing from heap\n");
            removeFromHeap(myHeap, argument);
        }
        else // function == 3
        {
            printf("%ld\n", myHeap->heap[0]);
        }
        numQueries--;
    }
    freeHeap(myHeap);
    return 0;
    
}
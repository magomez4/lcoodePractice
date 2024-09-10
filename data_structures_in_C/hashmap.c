#include <stdlib.h>
#include <stdbool.h>
// make a hashmap with a linked list
#define MAXBUCKETS 7919 // big prime number

typedef struct node{
    int key; 
    int val; 
    struct node* next;
}node;

typedef struct hashMap{
    node* buckets[MAXBUCKETS];
}hashMap;

hashMap* createHashMap()
{
    hashMap* newMap = (hashMap*)malloc(sizeof(hashMap));
    memset(newMap->buckets, 0, MAXBUCKETS*sizeof(node*));
    return newMap;
}

int getHashIndex(int key)
{
    return abs(key % MAXBUCKETS);
}

void insertMap(hashMap* obj, int key, int val)
{
    int bucketI = getHashIndex(key);
    node* current = obj->buckets[bucketI];
    while(current != NULL)
    {
        if(current->key == key)
        {
            // found key, update val
            current->val = val;
            return;
        }
        current = current->next;
    }
    // did not find key, so insert
    node* newNode = (node*)malloc(sizeof(node));
    newNode->key = key;
    newNode->val = val;
    newNode->next = obj->buckets[bucketI];
    obj->buckets[bucketI] = newNode;
}

void removeFromMap(hashMap* obj, int key)
{
    int bucketI = getHashIndex(key);
    node* current = obj->buckets[bucketI];
    node* prev = NULL;
    while(current!=NULL)
    {
        if(current->key == key)
        {
            // found key, now remove
            if(prev == NULL)
            {
                obj->buckets[bucketI] = NULL;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

bool mapContains(hashMap* obj, int key)
{
    int bucketI = getHashIndex(key);
    node* current = obj->buckets[bucketI];
    while(current != NULL)
    {
        if(current->key == key)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

int getVal(hashMap* obj, int key)
{
    int bucketI = getHashIndex(key);
    node* current = obj->buckets[bucketI];
    while(current != NULL)
    {
        if(current->key == key)
        {
            return current->val;
        }
        current = current->next;
    }
    // careful, is -1 valid for not found?
    return -1; 
}

void freeMap(hashMap* obj)
{
    for(int bucketI = 0; bucketI < MAXBUCKETS; bucketI++)
    {
        node* current = obj->buckets[bucketI];
        while(current != NULL)
        {
            node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(obj);
}
#include <stdlib.h>
#include <stdbool.h>
// make a hashset with a linked list
#define MAXBUCKETS 7919

typedef struct node {
    int val;
    struct Node* next;
} node;

typedef struct set {
    node* buckets[MAXBUCKETS];
} set;

set* createSet() 
{
    set* newSet = (set*)malloc(sizeof(set));
    if(newSet == NULL)
    {
        printf("BAD ALLOCATION");
        return NULL;
    }
    memset(newSet->buckets, 0, MAXBUCKETS * sizeof(node*));
    return newSet;
}

int getHashIndex(int val) 
{ 
    return abs(val % MAXBUCKETS); 
}

void insertSet(set* obj, int val) 
{
    int bucketI = getHashIndex(val);
    node* current = obj->buckets[bucketI];
    while(current != NULL)
    {
        if(current->val == val)
        {
            // value exists, no need to insert
            return;
        }
        current = current->next;
    }

    node* newNode = (node*)malloc(sizeof(node));
    if(newNode == NULL)
    {
        printf("BAD ALLOCATION");
        return;
    }
    newNode->val = val;
    newNode->next = obj->buckets[bucketI];
    obj->buckets[bucketI] = newNode;

}

void removeFromSet(set* obj, int val) 
{
    int bucketI = getHashIndex(val);
    node* current = obj->buckets[bucketI];
    node* prev = NULL;
    while(current != NULL)
    {
        if(current->val == val)
        {
            if(prev == NULL)
            {
                obj->buckets[bucketI] = current->next;
            }
            else
            {
                prev = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

bool setContains(set* obj, int val) 
{
    int bucketI = getHashIndex(val);
    node* current = obj->buckets[bucketI];
    while(current != NULL)
    {
        if(current->val == val)
        {
            return true;
        }
        current = current->next;
    }
    return false; // never found val
}

void freeSet(set* obj)
{
    for(int i = 0; i < MAXBUCKETS; i++)
    {
        node* current = obj->buckets[i];
        while(current != NULL)
        {
            node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(obj);
}
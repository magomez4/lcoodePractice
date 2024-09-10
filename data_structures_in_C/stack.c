#include <stdbool.h>
#include <stdlib.h>

// stack implemented with a linked list
typedef struct stackNode{
    int val; //change type as necessary
    struct stackNode* next;
}stackNode;

typedef struct stack{
    int size;
    stackNode* top; // can access directly
}stack;

stack* createStack()
{
    stack* newStack = (stack*)malloc(sizeof(stack));
    newStack->size = 0;
    newStack->top = NULL;
    return newStack;
}

void pushStack(stack* stk, int val)
{
    stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
    newNode->val = val;
    newNode->next = stk->top;
    stk->top = newNode;
    stk->size++;
}

void popStack(stack* stk)
{
    if(stk->top != NULL)
    {
        stackNode* temp = stk->top;
        stk->top = stk->top->next;
        free(temp);
        stk->size--;
    }
}

void freeStack(stack* stk)
{
    while(stk->top != NULL)
    {
        popStack(stk);
    }
    free(stk);
}

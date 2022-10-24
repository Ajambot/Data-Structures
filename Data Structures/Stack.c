#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct Stack{
    Node* head;
    int count;
}Stack;

Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if(stack)
    {
        stack->head=NULL;
        stack->count=0;
        return stack;
    }
}

int push(Stack* stack, int data)
{
    Node* newData = (Node*)malloc(sizeof(Node));
    if(newData)
    {
        newData->data=data;
        newData->next=stack->head;
        stack->head = newData;
        (stack->count)++;
        return 1;
    }
    return 0;
}

int pop(Stack* stack)
{
    if(!(stack->count))
        return -1;
    Node* dltPtr = stack->head;
    int retData = dltPtr->data;
    stack->head = dltPtr->next;
    free(dltPtr);
    (stack->count)--;
    return retData;
}

void print(Stack* stack)
{
    Node* ptr = stack->head;
    while(ptr!=NULL)
    {
        printf("%i ", ptr->data);
        ptr=ptr->next;
    }
    printf("\n");
}

void destroyStack(Stack* stack)
{
    Node* ptr = stack->head;
    Node* dlt;
    while(ptr!=NULL)
    {
        dlt=ptr;
        ptr=ptr->next;
        free(dlt);
    }
    free(stack);
    printf("Stack has been destroyed\n");
}

int main()
{
    Stack* stack = createStack();
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    push(stack, 5);
    print(stack);
    pop(stack);
    pop(stack);
    pop(stack);
    print(stack);
    destroyStack(stack);
}

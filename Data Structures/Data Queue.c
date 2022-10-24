#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct Queue{
    Node* front;
    Node* rear;
    int count;
}Queue;

Queue* createQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if(queue)
    {
        queue->front=NULL;
        queue->rear=NULL;
        queue->count=0;
        return queue;
    }
}

int enqueue(Queue* queue, int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode)
    {
        newNode->data=data;
        newNode->next=NULL;
        if(!(queue->count))
        {
            queue->front = newNode;
            queue->rear = newNode;
            (queue->count)++;
            return 1;
        }
        queue->rear->next = newNode;
        queue->rear = newNode;
        (queue->count)++;
        return 1;
    }
    return 0;
}

int dequeue(Queue* queue)
{
    if(!(queue->count))
        return -1;
    Node* dlt = queue->front;
    int retData = dlt->data;
    queue->front = dlt->next;
    free(dlt);
    (queue->count)--;
    return retData;
}

void print(Queue* queue)
{
    Node* ptr = queue->front;
    while(ptr!=NULL)
    {
        printf("%i ", ptr->data);
        ptr=ptr->next;
    }
    printf("\n");
}

void destroyQueue(Queue* queue)
{
    Node* ptr = queue->front;
    Node* dlt;
    while(ptr!=NULL)
    {
        dlt=ptr;
        ptr=ptr->next;
        free(dlt);
    }
    free(queue);
    printf("Queue has been destroyed\n");
}

int main()
{
    Queue* queue = createQueue();
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    print(queue);
    dequeue(queue);
    dequeue(queue);
    dequeue(queue);
    print(queue);
    destroyQueue(queue);
}

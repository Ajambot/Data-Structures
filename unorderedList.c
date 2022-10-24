#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct uList{
    Node* head;
    Node* rear;
    int count;
}uList;

uList* createUList()
{
    uList* list = (uList*)malloc(sizeof(uList));
    list->head = NULL;
    list->rear = NULL;
    list->count = 0;
    return list;
}

int insert(uList* list, int data)
{
    Node* newData = (Node*)malloc(sizeof(Node));
    if(newData)
    {
        newData->data=data;
        newData->next=NULL;
        if(!(list->count))
        {
            list->head=newData;
            list->rear = newData;
            (list->count)++;
            return 1;
        }
        list->rear->next = newData;
        list->rear = newData;
        (list->count)++;
        return 1;
    }
    return 0;
}

void rmv(uList* list, int data)
{
    Node* prev;
    Node* cur;
    prev = NULL;
    cur = list->head;
    while(cur!=NULL)
    {
        Node* dlt = (Node*)malloc(sizeof(Node));
        if(cur == list->head && cur->data==data)
        {
            list->head = cur->next;
            dlt = cur;
            cur=cur->next;
            free(dlt);
            (list->count)--;
        }
        else if(cur==list->rear && cur->data==data)
        {
            list->rear = prev;
            prev->next = cur->next;
            dlt = cur;
            cur=cur->next;
            free(dlt);
            (list->count)--;
        }
        else if(cur->data==data)
        {
            prev->next = cur->next;
            dlt = cur;
            cur=cur->next;
            free(dlt);
            (list->count)--;
        }
        else
        {
            prev=cur;
            cur=cur->next;
        }
    }
}

void print(uList* list)
{
    Node* cur = list->head;
    while(cur!=NULL)
    {
        printf("%i ", cur->data);
        cur=cur->next;
    }
    printf("\n");
}

void destroyUList(uList* list)
{
    Node* cur = list->head;
    Node* dlt;
    while(cur!=NULL)
    {
        dlt = cur;
        cur = cur->next;
        free(dlt);
    }
    free(list);
    printf("List has been destroyed\n");
}

void reverseList(uList* list)
{
    Node* prev, *cur, *next;
    cur=list->head;
    prev=NULL;
    next=NULL;
    list->rear = cur;
    while(cur!=NULL)
    {
        next=cur->next;
        cur->next = prev;
        prev=cur;
        cur=next;
    }
    list->head = prev;
}

int main()
{
    uList* list = createUList();
    insert(list, 1);
    insert(list, 1);
    insert(list, 1);
    insert(list, 2);
    insert(list, 2);
    insert(list, 3);
    insert(list, 4);
    print(list);
    reverseList(list);
    print(list);
    rmv(list, 2);
    print(list);
    rmv(list, 1);
    print(list);
    destroyUList(list);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct Olist
{
    Node* head;
    Node* rear;
    int count;
}Olist;

Olist* createOlist()
{
    Olist* list = (Olist*)malloc(sizeof(Olist));
    if(list)
    {
        list->head=NULL;
        list->rear=NULL;
        list->count=0;
        return list;
    }
}

int insert(Olist* list, int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode)
    {
        newNode->data = data;
        if((list->count)==0)
        {
            newNode->next = NULL;
            list->head = newNode;
            list->rear = newNode;
            (list->count)++;
            return 1;
        }
        Node* cur, *prev;
        cur = list->head;
        prev=NULL;
        while(cur!=NULL)
        {
            if(data<=cur->data)
            {
                if(cur==list->head)
                {
                    newNode->next = list->head;
                    list->head = newNode;
                    (list->count)++;
                    return 1;
                }
                newNode->next = prev->next;
                prev->next = newNode;
                (list->count)++;
                return 1;
            }
            if(cur==list->rear)
            {
                newNode->next=NULL;
                list->rear->next=newNode;
                list->rear=newNode;
                (list->count)++;
                return 1;
            }
            prev=cur;
            cur=cur->next;
        }
    }
    return 0;
}

void rmv(Olist* list, int data)
{
    if((list->count)==0 || data<list->head->data || data > list->rear->data)
        return;
    Node* cur, *prev;
    cur = list->head;
    prev=NULL;
    while(cur!=NULL)
    {
        //printf("%i ", data);
        if(cur->data>data)
            return;
        Node* dlt = (Node*)malloc(sizeof(Node));
        if(cur->data==data)
        {
            if(cur==list->head)
            {
                dlt = cur;
                list->head = cur->next;
                cur=cur->next;
                (list->count)--;
                free(dlt);
            }
            else if(cur==list->rear)
            {
                dlt = cur;
                list->rear = prev;
                prev->next = cur->next;
                cur=cur->next;
                (list->count)--;
                free(dlt);
            }
            else
            {
                prev->next = cur->next;
                dlt = cur;
                cur=cur->next;
                free(dlt);
                (list->count)--;
            }
        }
        else
        {
            prev=cur;
            cur=cur->next;
        }
    }
}

void print(Olist* list)
{
    Node* cur = list->head;
    while(cur!=NULL)
    {
        printf("%i ", cur->data);
        cur=cur->next;
    }
    printf("\n");
}

void destroyOlist(Olist* list)
{
    Node* cur = list->head;
    Node* dlt;
    while(cur!=NULL)
    {
        dlt = cur;
        cur=cur->next;
        free(dlt);
    }
    free(list);
}

void reverse(Olist* list)
{
    Node* prev, *cur, *next;
    prev=NULL;
    next=NULL;
    cur=list->head;
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
    Olist* list = createOlist();
    insert(list, 4);
    insert(list, 3);
    insert(list, 1);
    insert(list, 19);
    insert(list, -12);
    insert(list, 3);
    insert(list, 2);
    print(list);
    reverse(list);
    print(list);
    reverse(list);
    rmv(list, -12);
    rmv(list, 3);
    print(list);
    destroyOlist(list);
}

#include <stdio.h>
#include <stdlib.h>
/* Description: Program implements a doubly linked list. Each node contains 2 pointers: one to the next element and
 * one to the previous one. In main, we create a DLL (doubly linked list) and we insert 10 positive and 10 negative
 * numbers. We print the list, and then we create two sub-DLLs: one with only the positive numbers, and one with only
 * the negative numbers. We then print each list to verify they have been created correctly
*/
// Node Struct of Linked List
typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}Node;

// Linked List Metadata. DLL stands for Doubly Linked List
typedef struct DLL{
    Node* head;
    Node* rear;
    int count;
}DLL;

// Create the DLL
DLL* createDLL()
{
    DLL* list = (DLL*)malloc(sizeof(DLL)); // Allocate memory
    if(list) // Check if malloc worked
    {
        // Set default values
        list->count=0;
        list->head=NULL;
        list->rear=NULL;
        return list;
    }
}

// Inserts an element at the rear of the list
int insert(DLL* list, int data)
{
    Node* newData = (Node*)malloc(sizeof(Node)); // Allocate memory
    if(newData) { // Check if Mallloc worked
        newData->data = data; // Set data of new node
        if (!(list->count)) { // Check if list is not empty, then set next and prev to NULL and head and rear to the new node
            newData->next = NULL;
            newData->prev = NULL;
            list->head = newData;
            list->rear = newData;
            (list->count)++;
            return 1;
        }
        // If list is not empty:
        list->rear->next = newData; // Link rear to newNode
        newData->prev = list->rear; // Link newNode to rear
        newData->next = NULL; // NewNode is in rear, so next is NULL
        list->rear = newData; // new rear is newNode
        (list->count)++; // Count++
        return 1;
    }
    return 0;
}

// Create DLL with only positive numbers
DLL* positiveDLL(DLL* list)
{
    DLL* posDLL = createDLL(); // Use function we created earlier to create positive DLL
    Node* ptr = list->head; // Initialize Pointer to iterate through the list
    while(ptr!=NULL) // If we have not reached the end of the list
    {
        if((ptr->data)>=0) // If positive number
            insert(posDLL, ptr->data); // insert in positive DLL
        ptr=ptr->next; // ptr = next element
    }
    return posDLL;
}

// Create DLL with only negative numbers
DLL* negativeDLL(DLL* list)
{
    DLL* negDLL = createDLL(); // Use function we created earlier to create negative DLL
    Node* ptr = list->head; // Initialize pointer to head
    while(ptr!=NULL) // If not end of list
    {
        if((ptr->data)<0) // If num is negative
            insert(negDLL, ptr->data); // insert in list
        ptr=ptr->next; // Ptr = next element
    }
    return negDLL;
}

//Print all elements in a list
void print(DLL* list)
{
    Node* ptr = list->head; // Set ptr to head
    while(ptr!=NULL) // If not end of list
    {
        printf("%i ", ptr->data); // Print element
        ptr=ptr->next; // ptr = next element
    }
    printf("\n");
}

int main() {
    DLL* list = createDLL(); // Create DLL
    //Insert integers from -10 to 10 to DLL
    for(int i=-10; i<=10; i++)
    {
        if(!i) continue;
        insert(list, i);
    }
    print(list);
    DLL* pList = positiveDLL(list); // Create and initialize positive DLL
    DLL* nList = negativeDLL(list); // Create and initialize negative DLL
    printf("Positive Doubly Linked List: ");
    print(pList);
    printf("Negative Doubly Linked List: ");
    print(nList);
    return 0;
}

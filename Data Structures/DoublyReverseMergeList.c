#include <stdio.h>
#include<stdlib.h>
/* Description: Program implements a doubly linked list. Each node contains 2 pointers: one to the next element and
 * one to the previous one. In main, we create a DLL (doubly linked list) and we insert 5 numbers. We print the list,
 * and then we reverse it and store it in a new DLL. Finally, we merge both lists and print them
*/

// Node Struct of Doubly Linked List
typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}Node;
// Doubly Linked List Metadata. DLL stands for Doubly Linked List
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
        // set default values
        list->count =0;
        list->rear = NULL;
        list->head = NULL;
        return list;
    }
    printf("Malloc failed\n");
}

// Inserts an element at the rear of the list
int insert(DLL* list, int data)
{
    Node* newData = (Node*)malloc(sizeof(Node)); // Allocate memory
    if(newData) { // Check if malloc worked
        newData->data = data; // Set data of new node
        newData->next = NULL; // Set next node to NULL since we insert at the back
        if (!(list->count)) { // Check if list is not empty, then set prev to NULL and head and rear to the new Node
            newData->prev = NULL;
            list->rear = newData;
            list->head = newData;
            (list->count)++;
            return 1;
        }
        // If list is not empty
        list->rear->next = newData; // Link rear to newNode
        newData->prev = list->rear; // Link newNode to rear
        list->rear = newData; // new node is rear now
        (list->count)++; // count++
        return 1;
    }
    printf("Malloc failed\n"); // if newData is NULL, malloc did not work
    return 0;
}

// Create DLL with only negative numbers
DLL* reverse(DLL* list)
{
    DLL* revList = createDLL(); // Use function we created earlier to create reverse DLL
    Node* ptr = list->rear; // Initialize pointer to rear since we are reversing it
    while(ptr!=NULL)
    {
        insert(revList, ptr->data); // Insert elements from rear to head
        ptr = ptr->prev;
    }
    return revList;
}

// Create a new list with both lists and return it
// We could also just link list 1 to list 2 and it would be more efficient
// The method we are using has efficiency O(n) while linking the 2 lists has efficiency O(1)
DLL* mergeList(DLL* list, DLL* revList)
{
    DLL* mergeDLL = createDLL(); // Use function we created earlier to create mergeDLL
    Node* ptr = list->head; // Start from head and iterate to every node in list 1
    while(ptr!=NULL)
    {
        insert(mergeDLL, ptr->data); // insert every node in list 1 to new list
        ptr = ptr->next;
    }
    ptr = revList->head; // now do the same with list 2
    while(ptr!=NULL)
    {
        insert(mergeDLL, ptr->data);
        ptr = ptr->next;
    }
    return mergeDLL;
}

// Prints the list given
void print(DLL* list)
{
    Node* ptr = list->head;
    while(ptr!=NULL)
    {
        printf("%i ", ptr->data);
        ptr=ptr->next;
    }
    printf("\n");
}

int main() {
    DLL* list = createDLL();
    for(int i=1; i<=64; i*=2)
    {
        insert(list, i);
    }
    print(list);
    DLL* revList = reverse(list);
    print(revList);
    DLL* mergeDLL = mergeList(list, revList);
    print(mergeDLL);
    return 0;
}

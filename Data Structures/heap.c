#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// The program implements a max heap with insertion and reheapUp functions. It inserts
// 10 numbers and prints the heap

// Max Heap data structure
typedef struct Heap{
    int array[100];
    int size;
    int maxSize;
    int lastIndex;
}Heap;

// Function to create maxHeap
Heap* createHeap()
{
    Heap* heap = (Heap*)malloc(sizeof(Heap)); // allocate memory
    if(heap) // if malloc worked
    {
        // initialize default values
        (heap->size)=0;
        (heap->maxSize)=100;
        (heap->lastIndex)=0;
        for(int i=1; i<=heap->maxSize-1; i++)
            heap->array[i]=INT_MIN;
        return heap;
    }
}

// Function to reheap Up
void reheapUp(Heap* heap, int lastIndex)
{
    // While parent is < current node current node is not the root, swap them
    while(heap->array[(int)floor(lastIndex/2.0)]<heap->array[lastIndex] && lastIndex>1) {
        int temp = heap->array[lastIndex];
        heap->array[lastIndex] = heap->array[(int) floor(lastIndex / 2.0)];
        heap->array[(int) floor(lastIndex / 2.0)] = temp;
        lastIndex = (int) floor(lastIndex / 2.0);
    }
}

// Function to reheap down
void reHeapDown(Heap* heap, int root)
{
    int rKey = INT_MIN;
    int lKey = INT_MIN;
    int maxKey= INT_MIN;
    if(2*root <= heap->lastIndex) // If left subtree exists, set lKey to left subtree vallue
        lKey = heap->array[2*root];
    if(2*root+1 <= heap->lastIndex) // If left subtree exists, set lKey to left subtree vallue
        rKey = heap->array[2*root+1];
    // Set maximum key index between lkey and rkey to maxKey
    if(lKey > rKey)
        maxKey = 2*root;
    else
        maxKey = 2*root+1;

    // If root < maxKey, swap them and reHeapDown
    if(heap->array[root] < heap->array[maxKey])
    {
        int temp = heap->array[maxKey];
        heap->array[maxKey] = heap->array[root];
        heap->array[root] = temp;
        reHeapDown(heap, maxKey);
    }
}
// Function to delete in a heap
int delete(Heap* heap)
{
    printf("Deleting root: %i\n", heap->array[1]);
    int delNum=INT_MIN;
    if(!(heap->size)) // If heap is empty, we can't delete
        return delNum;
    delNum = heap->array[1]; // delNum = data to delete (i.e. root)
    // Exchange root and last element
    heap->array[1] = heap->array[heap->lastIndex];
    heap->array[heap->lastIndex] = INT_MIN;
    (heap->lastIndex)--;
    (heap->size)--;
    reHeapDown(heap, 1); // reHeapDown
    return delNum;
}

// Function to insert a number
int insert(Heap* heap, int num)
{
    // If array is not full, insert in last index and update last index and size
    if(heap->size!=heap->maxSize)
    {
        heap->array[++(heap->lastIndex)] = num;
        (heap->size)++;
        reheapUp(heap, heap->lastIndex);
        return 1;
    }
    return 0;
}

// Function to print the heap in BFS traversal
void print(Heap* heap)
{
    for(int i=1; i<=heap->lastIndex; i++) {
        printf("%i ", heap->array[i]);
    }
}

// Insert 10 numbers and print
int main() {
    Heap* heap = createHeap();
    insert(heap, 10);
    insert(heap, 20);
    insert(heap, 30);
    insert(heap, 40);
    insert(heap, 50);
    insert(heap, 60);
    insert(heap, 75);
    insert(heap, 84);
    insert(heap, 93);
    insert(heap, 95);
    print(heap);
    printf("\n");
    for(int i=0; i<5; i++)
    {
        delete(heap);
        print(heap);
        printf("\n");
    }
    free(heap);
    return 0;
}

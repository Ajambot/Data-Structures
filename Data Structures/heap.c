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
        heap->size=0;
        heap->maxSize=100;
        heap->lastIndex=0;
        for(int i=1; i<=heap->maxSize; i++)
            heap->array[i]=INT_MIN;
        return heap;
    }
}

// Function to reheap Up
void reheapUp(Heap* heap, int lastIndex)
{
    // While parent is < current node current node is not the root, swap them
    while(heap->array[(int)floor(lastIndex/2.0)]<heap->array[lastIndex] && lastIndex>=1)
    {
        int temp = heap->array[lastIndex];
        heap->array[lastIndex] = heap->array[(int)floor(lastIndex/2.0)];
        heap->array[(int)floor(lastIndex/2.0)] = temp;
        lastIndex = (int)floor(lastIndex/2.0);
    }
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
    for(int i=1; i<=heap->maxSize; i++) {
        if(heap->array[i]==INT_MIN)
            return;
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
    return 0;
}

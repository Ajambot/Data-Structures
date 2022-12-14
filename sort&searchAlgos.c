#include <stdio.h>
#include<limits.h>

// Function to swap two values in an array. Reused in multiple sort methods
void swap(int array[], int a, int b)
{
    int temp = array[b];
    array[b]=array[a];
    array[a]=temp;

}

// Function to perform selection sort on an array
void selSort(int array[], int n)
{
    // Walker is the index of the first unsorted value.
    for(int walker=0; walker<n; walker++)
    {
        int minIndex=walker;
        // Check each value after the walker and find the minimum
        for(int i=walker; i<n; i++)
            if(array[i]<array[minIndex])
                minIndex = i;
        swap(array, walker, minIndex); // Swap the minimum value with the first unsorted value
    }
}

// reHeapDown function for heap sort. Readjusts heap after deletion
void reheapDown(int heap[], int n, int cur)
{
    int ltree = cur*2+1; // left child of current node
    int rtree = cur*2+2; // right child of current node
    int maxtree= (heap[ltree]>heap[rtree])? ltree : rtree; // saves the index of the max children of the current node
    // if current element is smaller than the maximum child, swap them and reheap down
    if(heap[cur]<heap[maxtree] && maxtree<n)
    {
        swap(heap, cur, maxtree);
        reheapDown(heap, n, maxtree);
    }
}

// Deletes the top/max element of the heap and returns it
int deleteHeap(int heap[], int n)
{
    int retValue = heap[0]; // We return current max
    heap[0] = heap[--n]; // Swap root with last element
    reheapDown(heap, n, 0); // reHeapDown to adjust heap
    return retValue;
}

// reHeapUp function for heap sort. Readjusts heap after insertion
void reheapUp(int heap[], int cur)
{
    int parent = (cur-1)/2; // Parent of current node
    if(heap[cur]>heap[parent] && parent>=0) // If parent exists and is smaller than current node, swap them and reheap up
    {
        swap(heap, parent, cur);
        reheapUp(heap, parent);
    }
}

// Inserts a value in the heap
void insert(int heap[], int n, int num)
{
    heap[n++] = num; // Insert element in last node
    reheapUp(heap, n-1); // reheap last element up if needed
}

// Function to perform heap sort on an array
void heapSort(int array[], int n)
{
    int heap[n];
    for(int i=0; i<n; i++) insert(heap, i, array[i]); // Insert all of the elements in the array in a heap
    for(int i=0; i<n; i++) array[n-1-i] = deleteHeap(heap, n-i); // Get maximum element and insert it in last possible index
}

// Function to perform insertion sort on an array
void insertionSort(int array[], int n)
{
    // sorted is the index of the first unsorted element
    for(int sorted=1; sorted<n; sorted++)
    {
        int cur = sorted;
        while(cur>0 && array[cur]<array[cur-1]) // Check if element is in the right position, if not swap with previous element
        {
            swap(array, cur, cur-1);
            cur--;
        }
    }
}

// Function to perform bubble sort on an array
void bubbleSort(int array[], int n)
{
    for(int i=0; i<n; i++)
    {
        int flagSorted=1; // Flags if we didn't make any swaps on the innermost loop
        for(int o=0; o<n-i; o++)
        {
            if(array[o]>array[o+1]) // If current element is bigger than next, bubble up
            {
                swap(array, o, o+1);
                flagSorted=0; // Swap was made
            }
        }
        if(flagSorted) break; // If no swaps were made in last iteration, list is sorted
    }
}

// Function to perform binary search on a sorted array
int binarySearch(int array[], int l, int r, int val)
{
    if(l>r) return -1; // If left pivot is bigger than right pivot, element is not in list
    int mid = (l+r)/2;
    if(array[mid]<val) return binarySearch(array, mid+1, r, val); // if value is bigger than mid, recursively look in right half
    else if(array[mid]>val) return binarySearch(array, l, mid-1, val); // if value is smaller than mid, recursively look in left half
    else return mid; // Value is in mid, return index
}


int main()
{
    int n;
    printf("Size of the array: ");
    scanf("%i", &n);
    int array[n];
    printf("Values (space separated): ");
    // menu
    for(int i=0; i<n; i++) scanf("%i", &array[i]);
    printf("Select method to sort:\n\t"
           "1. Bubble Sort\n\t"
           "2. Selection Sort\n\t"
           "3. Insertion Sort\n\t"
           "4. Heap Sort\n");

    int sortMethod;
    scanf("%i", &sortMethod);

    switch(sortMethod)
    {
        case 1:
            bubbleSort(array, n);
            break;
        case 2:
            selSort(array, n);
            break;
        case 3:
            insertionSort(array, n);
            break;
        case 4:
            heapSort(array, n);
            break;
        default:
            printf("Sorry, your option is not in the list. Terminating program.");
            return 1;
    }
    printf("Sorted Array: ");
    for(int i=0; i<n; i++) printf("%i ", array[i]);

    // Binary search
    int searchVal;
    printf("\nSearch for a value in the array: ");
    scanf("%i", &searchVal);
    (binarySearch(array, 0, n, searchVal)!=-1)? printf("Value is in index %i\n", binarySearch(array, 0, n, searchVal)) : printf("Value not found\n");
    return 0;
}

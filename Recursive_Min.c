#include <stdio.h>

/* Program: Assignment 1 - Problem 3
 * Student: Martin Morales Arana
 * Class: Comp-2412-FA - Data Structures
 * Professor: Dr. Muhammad Asaduzzaman, TA: Ahmed Aboulfotouh
 *
 * Description: Program uses a recursive function to determine the minimum
 * integer in an array. i is the offset and size is the size of the array
*/
int minNum(int arr[], int i, int size)
{
    if(i==size-1) // If reach end of array
        return arr[i]; // return last element

    // return minimum between current integer and all the integers after
    return (arr[i]<minNum(arr, i+1, size))? arr[i]:minNum(arr, i+1, size);
}

int main() {
    // Initialize array with 6 random integers
    int arrNum[] = {2, 5, -57, 32, -2, 25};
    // print minimum number in array
    printf("%i\n", minNum(arrNum, 0, sizeof(arrNum)/sizeof(arrNum[0])));
    return 0;
}

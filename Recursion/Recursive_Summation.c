#include <stdio.h>

/* Description: Program uses a recursive function to determine the summation
 * of the numbers from 1 to n
*/

// Computes and return sum of 1 to n
int sum(int n)
{
    if(n==1) // Base case: if n==1 return n
        return n;

    return n+sum(n-1); // Compute n-1 and add it to n
}

int main() {

    int x=1250000; // Test n=4
    x=sum(x); // x = sum from 1 to 4
    printf("%i\n", x); // print result
    return 0;
}

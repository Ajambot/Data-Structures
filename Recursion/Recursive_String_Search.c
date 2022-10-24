#include <stdio.h>

/* Description: Program uses a recursive function to determine the number of
 * occurrences of a character in a string
*/

// c is character to look for, i is current index
int charOccurrences(char string[], char c, int i)
{
    if(string[i]=='\0') // If we reach the end of the string, return 0
        return 0;
    if(string[i]==c) // If current character = character we are looking for
        return 1+charOccurrences(string, c, i+1); // return occurrences of c in the rest of the string +1
    return 0+charOccurrences(string, c, i+1); // else, return occurrences of c in the rest of the string +0
}

int main() {
    // Search for occurrences of l in Hello World
    printf("%i\n", charOccurrences("Hello World!", 'l', 0));
    return 0;
}

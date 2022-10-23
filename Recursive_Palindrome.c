#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Program: Assignment 1 - Problem 2
 * Student: Martin Morales Arana
 * Class: Comp-2412-FA - Data Structures
 * Professor: Dr. Muhammad Asaduzzaman, TA: Ahmed Aboulfotouh
 *
 * Description: Program uses a recursive function to determine if a string
 * is a palindrome by checking if the extremes of the string are the same
 * i.e. if the first half is equal to the second half
*/

// l is leftmost offset, r is rightmost offset
int palindrome(char string[], int l, int r)
{
    while(string[l]==' ') // If space in leftmost character+offset
        l++; // Increment offset by one. i.e. ignore space
    while(string[strlen(string)-1-r]==' ') // If space in rightmost character - offset
        r++; // Increment offset by one. i.e. ignore space

    if(l>=strlen(string)-1-r) // If leftmost offset >= than rightmost character - offset. i.e. we have checked the whole string
        return 1; // It is a palindrome, return 1

    // If current leftmost character is not equal to current rightmost character (ignoring capitalization)
    if(tolower(string[l]) != tolower(string[strlen(string)-1-r]))
        return 0; // Not a palindrome, return 0

    return palindrome(string, l+1, r+1); // Check rest of string for palindrome
}

int main() {

    // Create 3 strings to check for palindrome
    char s[100] = "    S s         A       s             S       ";
    char s2[100] = "do GOD";
    char s3[100] = "notAPalindrome";

    if(palindrome(s, 0, 0)) //Check if s is a palindrome
        printf("%s is a palindrome\n", s);
    else
        printf("%s is not a palindrome\n", s);

    if(palindrome(s2, 0, 0)) // Check if s2 is a palindrome
        printf("%s is a palindrome\n", s2);
    else
        printf("%s is not a palindrome\n", s2);

    if(palindrome(s3, 0, 0)) // Check if s3 is a palindrome
        printf("%s is a palindrome\n", s3);
    else
        printf("%s is not a palindrome\n", s3);

    return 0;
}

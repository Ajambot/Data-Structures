#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* printReverse(char *s)
{
    char *temp=(char*)malloc(strlen(s)+1);
    if(*(s+1)=='\0') {
        return s;
    }
    //printf("WORLD");
    temp = printReverse(s+1);
    printf("%s %s\n", s, temp);
    strncat(temp, s, 1);
    return temp;
}

int main() {
    char word[100]="Hello World";
    printf("String: %s", printReverse(word));
    return 0;
}

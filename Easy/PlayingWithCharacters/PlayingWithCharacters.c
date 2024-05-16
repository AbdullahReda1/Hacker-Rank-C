#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char c, s[100], sentence[100];

    scanf("%c", &c);					// Read char
    scanf("%s\n", s);					// Read word
    scanf("%[^\n]%*c", sentence);		// Read line

    printf("%c\n%s\n%s", c, s, sentence);
       
    return 0;
}
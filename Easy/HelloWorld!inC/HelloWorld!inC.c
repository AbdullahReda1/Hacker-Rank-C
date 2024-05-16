#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{
	
    char s[100];
    scanf("%[^\n]%*c", &s);
  	/*
		Here, [] is the scanset character. ^\n stands for taking input until a newline isn't encountered. 
		Then, with this %*c, it reads the newline character and here, the used * indicates that this newline character is discarded.
		Note: The statement: scanf("%[^\n]%*c", s); will not work because the last statement will read a newline character, 
		\n, from the previous line. This can be handled in a variety of ways. One way is to use scanf("\n"); before the last statement.
	*/
	
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    printf("Hello, World!\n%s\n", s);
    
    return 0;
}
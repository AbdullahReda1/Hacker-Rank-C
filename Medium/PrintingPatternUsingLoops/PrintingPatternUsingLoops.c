#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    int n;
    scanf("%d", &n);

  	// Complete the code to print the pattern.
    for (int i = n; i >= -n; i--) {
        if (i == 0) {
            i -= 2;
        }
        for (int j = n; j >= -n; j--) {
            if (j == 0) {
                j -= 2;
            }
            if   (abs(j) > abs(i)) { printf("%d ", abs(j)); }
            else                   { printf("%d ", abs(i)); }
        }
        printf("\n");
    }

    return 0;
}
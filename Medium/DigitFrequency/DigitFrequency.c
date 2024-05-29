#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char * s = malloc(1024 * sizeof(char));
    scanf("%[^\n]", s);
    
    int arrCounter[10] = {0};
    
    int i = 0;
    while (s[i] != '\0') {
        if ((s[i] >= '0') && (s[i] <= '9')) {
            arrCounter[(s[i] - 48)]++;
        }
        i++;
    }
    
    for (int j = 0; j < 10; j++) {
        printf("%d ", arrCounter[j]);
    }
    
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
	
    int n;
    scanf("%d", &n);
    
    //Complete the code to calculate the sum of the five digits on n.
    int firstDigit  = ((n          )    / 10000);
    int secondDigit = ((n  % 10000)     / 1000 );
    int thirdDigit  = ((n  % 1000)      / 100  );
    int fourthDigit = ((n  % 100)       / 10   );
    int fifthDigit  = ((n  % 10)        / 1    );
    
    int Sumof5Digits = firstDigit + secondDigit + thirdDigit + fourthDigit + fifthDigit;
    
    printf("%d", Sumof5Digits);
    
    return 0;
}
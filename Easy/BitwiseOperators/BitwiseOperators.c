#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//Complete the following function.
void calculate_the_maximum(int n, int k) {
  //Write your code here.
  int maxAnd = 0, maxOr = 0, maxXor = 0;
  int And       , Or       , Xor       ;
  
  for (int i = 1; i < n; i++) {
    for (int j = (i + 1); j <= n; j++) {
        And = i & j;    Or  = i | j;    Xor = i ^ j;
        
        if((And < k) && (And > maxAnd)) {
            maxAnd = And;
        }
        
        if((Or  < k) && (Or  > maxOr )) {
            maxOr  = Or ;
        }
        
        if((Xor < k) && (Xor > maxXor)) {
            maxXor = Xor;
        }
    }
  }
  
  printf("%d\n%d\n%d\n", maxAnd, maxOr, maxXor);
}

int main() {
    int n, k;
  
    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);
 
    return 0;
}
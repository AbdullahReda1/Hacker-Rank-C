#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//Complete the following function.
int find_nth_term(int n, int a, int b, int c) {
	//Write your code here.
	/* 3 is the key of the series, where the otherwise condition is upper than 3 */
	/* so, if this number changed according to the series, this will change 1st condition (n > 3)
	       and number of operations (3 additions - also the operation is according to the series type -)
		   and Nth back into series (n - 3 - into the recursion function -) and number of sequence elements ([3]) */
	while (n >= 1 && n <= 20) {
		if (n > 3) {
			a += b + c;
			b += a + c;
			c += a + b;
			return find_nth_term(n - 3, a, b, c);
		} else {
			int sequence[3] = {a, b, c};
			return sequence[n - 1];
		}
	}
	return 0;
}

int main() {
    int n, a, b, c;
  
    scanf("%d %d %d %d", &n, &a, &b, &c);
    int ans = find_nth_term(n, a, b, c);
 
    printf("%d", ans); 
    return 0;
}
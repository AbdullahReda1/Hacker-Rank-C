#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//Complete the following function.
int find_nth_term(int n, int a, int b, int c) {
	//Write your code here.
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
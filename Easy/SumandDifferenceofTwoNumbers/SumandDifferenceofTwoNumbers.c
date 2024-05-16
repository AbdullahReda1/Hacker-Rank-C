#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int x,y;
    float n,m;
    
	scanf("%d %d", &x, &y);
    scanf("%f %f", &m, &n);
    
    printf("%d %d\n", x+y, x-y);
    printf("%.1f %.1f\n", m+n, m-n);
	
	/* "%.1f" float scaled to  decimal place */
    
    return 0;
}
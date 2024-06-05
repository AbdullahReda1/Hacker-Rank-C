#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

void sort_by_area(triangle* tr, int n) {
	/**
	* Sort an array a of the length n
	*/
    // Allocate an array to store the areas of the triangles
    double *area = (double *)malloc(n * sizeof(double));

    for (int i = 0; i < (n); i++) {
    	double p = 0.0;
    	p = ((tr[i].a) + (tr[i].b) + (tr[i].c)) / 2.0;
    	area[i] =
    	sqrt(p * (p - (tr[i].a)) * (p - (tr[i].b)) * (p - (tr[i].c)));
    }

    // Bubble sort to sort triangles by area
    for (int i = 0; i < (n - 1); i++) {
        for (int j = 0; j < (n - i - 1); j++) {
        	if (area[j] > area[j + 1]) {
        		double temp_area = area[j];
        		area[j] = area[j + 1];
        		area[j + 1] = temp_area;

        		// Swap the corresponding triangles
        		triangle temp = tr[j];
        		tr[j] = tr[j + 1];
        		tr[j + 1] = temp;
        	}
        }
    }
}

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}
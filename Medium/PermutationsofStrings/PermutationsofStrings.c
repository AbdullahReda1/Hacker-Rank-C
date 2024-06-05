#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/

    // Traverse the array from right to left to find the first pair of elements
    // where the previous element is smaller than the current element.
    for (int i = n - 2; i >= 0; i--) {
        // Compare the current element with the next element.
        if (strcmp(s[i], s[i + 1]) < 0) {
            // If such a pair is found, traverse the array from right to left again
            // to find the first element that is greater than the current element.
            for (int j = n - 1; j > i; j--) {
				// Find the smallest element to the right of `i` that is larger than `s[i]`
                if (strcmp(s[j], s[i]) > 0) {
                    // Swap these two elements.
                    char *temp = s[i];
                    s[i] 	   = s[j];
                    s[j] 	   = temp;

                    // Reverse the sequence of elements to the right of the current element.
                    for (int left = i + 1, right = n - 1; left < right; left++, right--) {
                        char *temp = s[left] ;
                        s[left]    = s[right];
                        s[right]   = temp	 ;
                    }
                    
                    // Return 1 to indicate that the next permutation was found.
                    return 1;
                }
            }
        }
    }

    // Return 0 to indicate that no next permutation was found (already at the last permutation).
    return 0;
}

int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}
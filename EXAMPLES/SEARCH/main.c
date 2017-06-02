#include <stdio.h>

int binary_search(int *a, int n, int x)
{
    int i = 0, j = n - 1;
    
    while (i <= j)
    {
        int k = (i + j) / 2;
        
        if (a[k] == x)
        {
            return k;
        }
        else if (a[k] < x)
        {
            i = k + 1;
        }
        else 
        {
            j = k - 1;
        }
    }
    return -1;
}

int main (void) 
{
    int a[] = {-31, 0, 1, 2, 2, 4, 65, 83, 99, 782};
    int n = sizeof a / sizeof a[0];
    int x = 2;
    int i = binary_search(a, n, x);
    printf("%d is at index %d\n", x, i);
    x = 5;
    i = binary_search(a, n, x);
    printf("%d is at index %d\n", x, i);
    return 0;
}
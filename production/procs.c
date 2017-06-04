
#include "array.h"


int in_set( Array *a, int len,  char *match)
{
    int i = 0, j = len - 1, ret ;
    while (i <= j)
    {
        int k = (i + j) / 2;
        ret = strcmp(a -> array[k].name, match);
        if (ret > 0)
        {
            j = k - 1;
        } else if (ret < 0)
        {
            i = k + 1;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

void diff(Array *x, int lenx, Array *y, int leny)
{
    int i;
	for (i = 0; i < lenx; i++)
	{
		if (x->array[i].name && !in_set(y, leny, x->array[i].name)) printf("  archivo -> %s\n", x->array[i].name);
	}
}
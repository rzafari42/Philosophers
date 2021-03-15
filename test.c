
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int *c;
    int i;

    i = 0;
    c = (int *)malloc(sizeof(int) * 4);
    c[12] = 12;
    i = 0;
    while (i <= 20)
    {
        printf("c[%d] = %d\n", i, c[i]);
        i++;
    }
    printf("c[%d] = %d\n", 12, c[12]);
    return (0);
}

#include <stdio.h>

/*
birds and bees
believe it or not
*/

int main()
{
    char str[30000][50], x;
    int i = 0;
    while (scanf("%s%c", &str[i], &x))
    {
        if (x == '\n')
        {
            break;
        }
        i++;
    }
    while (i >= 0)
    {
        printf("%s ", str[i]);
        i--;
    }
    printf("\n");
    return 0;
}
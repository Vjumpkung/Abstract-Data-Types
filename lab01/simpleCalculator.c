#include <stdio.h>
int main()
{
    float a, b;
    char x;
    scanf("%f %s %f", &a, &x, &b);
    if (x == 43)
    {
        printf("%.0f", a + b);
    }
    else if (x == 45)
    {
        printf("%.0f", a - b);
    }
    else if (x == 42)
    {
        printf("%.0f", a * b);
    }
    else if (x == 47)
    {
        printf("%.2f", a / b);
    }
    else if (x == 37)
    {
        int c, d;
        c = (int)a;
        d = (int)b;
        printf("%d", c % d);
    }
    else
    {
        printf("Unknown Operator");
    }
    printf("\n");
    return 0;
}

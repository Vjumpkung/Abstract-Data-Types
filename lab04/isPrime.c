#include <stdio.h>
#include <math.h>

int isPrime(int n)
{
    if (n < 2)
    {
        return 0;
    }
    int i;
    for (i = 2; i < sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int a;
    scanf("%d", &a);
    printf("%d\n", isPrime(a));
    return 0;
}

// Big-Oh notation is O(sqrt(n))
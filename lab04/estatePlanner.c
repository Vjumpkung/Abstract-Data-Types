#include <stdio.h>
#include <math.h>

int px(int m)
{
    int x = 0, p = 0;
    while (1)
    {
        x = pow(2, p);
        if (x > m)
        {
            x = pow(2, p - 1);

            break;
        }
        p++;
    }
    return x;
}

int can(int n)
{
    return ((int)(log(n) / log(2))) == (log(n) / log(2));
}

int f(int n, int m)
{
    if (n <= 0 || m <= 0)
    {
        return 0;
    }
    if (n < m)
    {
        int x = px(n);
        return f(x, x) + f(x, m - x) + f(n - x, m);
    }
    else if (n > m)
    {
        return f(m, n);
    }
    else if (!(can(m) && can(n)))
    {
        int x = px(m);
        return f(x, x) + f(n - x, m) + f(n - x, x);
    }
    else
    {
        return 1;
    }
}

int main()
{
    int r, c;
    scanf("%d %d", &r, &c);
    printf("%d\n", f(r, c));

    return 0;
}

// Big-Oh notation is O(rc)

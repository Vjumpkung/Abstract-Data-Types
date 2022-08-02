#include <stdio.h>
int main()
{
    unsigned int t;
    scanf("%u", &t);
    int d, h, m, s;
    m = t / 60;
    s = t % 60;
    h = m / 60;
    m = m % 60;
    d = h / 24;
    h = h % 24;
    printf("%d %d %d %d\n", d, h, m, s);
    return 0;
}

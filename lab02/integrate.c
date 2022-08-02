#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, A, B, n;
    double pi = 3.141592653589793;
    double total_area = 0;
    double temp_x, temp_y1, temp_y2;
    scanf("%lf %lf %lf %lf %lf", &a, &b, &A, &B, &n);
    int i;
    temp_x = (b - a) / n;
    for (i = 0; i < n; i++)
    {
        temp_y1 = A * sin(pi * (a + (i)*temp_x) / B);
        temp_y2 = A * sin(pi * (a + (i + 1) * temp_x) / B);
        total_area += (1.0 / 2.0) * temp_x * (temp_y1 + temp_y2);
        // printf("%lf %lf %lf %lf\n", a + (i) * ((b - a) / n), a + (i + 1) * ((b - a) / n), temp_y1, temp_y2);
    }
    printf("%.5f\n", total_area);
    return 0;
}

#include <stdio.h>
#include <math.h>

long int fact(int n)
{
    if (n == 1 || n == 0)
    {
        return 1;
    }
    else
    {
        return n * fact(n - 1);
    }
}

double mySin(double x)
{
    double pi = 3.141592653589793;
    int i;
    double sum = 0;
    x = x * pi / 180;
    for (i = 0; i < 10; i++)
    {
        sum += pow(-1, i) * ((pow(x, 2 * i + 1)) / fact(2 * i + 1));
    }
    return sum;
}

double myCos(double x)
{
    return sqrt(1 - pow(mySin(x), 2));
}

double myTan(double x)
{
    return mySin(x) / myCos(x);
}

int main()
{
    double degree;
    scanf("%lf", &degree);
    printf("%.14lf %.14lf %.14lf\n", mySin(degree), myCos(degree), myTan(degree));
    return 0;
}
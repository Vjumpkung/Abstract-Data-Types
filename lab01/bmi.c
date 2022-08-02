#include <stdio.h>
int main()
{
    float w, h, ans;
    scanf("%f %f", &w, &h);
    ans = w / ((h / 100) * (h / 100));
    printf("BMI: %.4f ", ans);
    if (ans >= 30)
    {
        printf("and you are obese", ans);
    }
    else if (ans >= 25 && ans < 30)
    {
        printf("and you are overweight", ans);
    }
    else if (ans >= 18.6 && ans < 25)
    {
        printf("and you are healthy", ans);
    }
    else
    {
        printf("and you are underweight", ans);
    }
    printf("\n");
    return 0;
}

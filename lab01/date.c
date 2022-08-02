#include <stdio.h>
int main()
{
    char x;
    int d, m, y;
    scanf("%d%c%d%c%d", &d, &x, &m, &x, &y);
    int today_days_drom_month = 0;
    int this_month;
    int i;
    for (i = 1; i <= m - 1; i++)
    {
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
        {
            this_month = 31;
            today_days_drom_month += this_month;
        }
        else if (i == 4 || i == 6 || i == 9 || i == 11)
        {
            this_month = 30;
            today_days_drom_month += this_month;
        }
        else if (i == 2)
        {
            if (y % 4 == 0 && y % 100 != 0)
            {
                this_month = 29;
            }
            else if (y % 400 == 0)
            {
                this_month = 29;
            }
            else
            {
                this_month = 28;
            }
            today_days_drom_month += this_month;
        }
    }
    printf("%d\n", d + today_days_drom_month);
    return 0;
}
#include <stdio.h>

char m[12][4] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
char d[7][4] = {"Thu", "Fri", "Sat", "Sun", "Mon", "Tue", "Wed"};
int wan[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

typedef struct datetime
{
    int date;
    int month;
    int year;
    int dayOfWeek;
    int hour;
    int minute;
    int second;
} datetime_t;

datetime_t createDate(unsigned int timestamp)
{
    int t = timestamp;
    int d, h, m, s, month = 0, day = 0, year = 0;
    int temp_year;
    m = t / 60;
    s = t % 60;
    h = m / 60;
    m = m % 60;
    d = h / 24;
    h = h % 24;
    day = d;
    int i = 0;
    while (d - wan[i] >= 0)
    {
        if (month + 1 == 12)
        {
            year++;
            month = 0;
        }
        else
        {
            month++;
        }
        temp_year = 1970 + year;
        if (((temp_year) % 4 == 0 && ((temp_year) % 100 != 0)) || ((temp_year) % 400 == 0))
        {
            wan[1] = 29;
        }
        else
        {
            wan[1] = 28;
        }
        d -= wan[i];
        if (i + 1 >= 12)
        {
            i = 0;
        }
        else
        {
            i++;
        }
    }
    int temp_month = month;
    struct datetime NewDate;
    NewDate.second = s;
    NewDate.minute = m;
    NewDate.hour = h;
    NewDate.dayOfWeek = day % 7;
    NewDate.year = 1970 + year;
    NewDate.month = 1 + month;
    NewDate.date = 1 + d;
    return NewDate;
}

void printDate(datetime_t datex)
{
    printf("%s %d %s %d %02d:%02d:%02d\n", d[datex.dayOfWeek], datex.date, m[datex.month - 1], datex.year, datex.hour, datex.minute, datex.second);
}

int main()
{
    datetime_t inputDate;
    int timestamp;
    scanf("%d", &timestamp);
    inputDate = createDate(timestamp);
    printDate(inputDate);
    return 0;
}
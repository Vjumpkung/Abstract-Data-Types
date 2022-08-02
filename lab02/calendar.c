#include <stdio.h>

// 1   5   9   13  17  21  25
// Sun Mon Tue Wed Thu Fri Sat

int search(int data, int mode)
{
    int arr[] = {1, 5, 9, 13, 17, 21, 25};
    int i;
    if (mode == 0)
    {
        for (i = 0; i < 7; i++)
        {
            arr[i] += 2;
        }
    }
    else if (mode == 1)
    {
        for (i = 0; i < 7; i++)
        {
            arr[i] += 1;
        }
    }
    for (i = 0; i < 7; i++)
    {
        if (arr[i] == data)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    char m[12][20] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int wan[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year, month;
    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter month: ");
    scanf("%d", &month);
    int i;
    printf("====================\n%s %d\nSun Mon Tue Wed Thu Fri Sat\n", m[month - 1], year);
    int start_point = 0;
    int start_year = 1990;
    while (start_year <= year)
    {
        if (((start_year - 1) % 4 == 0 && ((start_year - 1) % 100 != 0)) || ((start_year - 1) % 400 == 0))
        {
            start_point += 2;
        }
        else
        {
            start_point += 1;
        }
        if (start_point > 6)
        {
            start_point = start_point - 7;
        }
        // printf("Y%d : start date is %d\n", start_year, start_point);
        start_year++;
    }

    int start_month = 1;

    if (((year) % 4 == 0 && ((year) % 100 != 0)) || ((year) % 400 == 0))
    {
        wan[1] = 29;
    }

    while (start_month < month)
    {
        int start_day = 1;
        while (start_day <= wan[start_month - 1])
        {
            start_point += 1;
            if (start_point > 6)
            {
                start_point = 0;
            }
            // printf("%d M %d D : start date is %d\n", start_month, start_day, start_point);
            start_day += 1;
        }
        start_month += 1;
    }

    // space 27
    // printf("start date is %d\n", start_point);

    int points[] = {1, 5, 9, 13, 17, 21, 25};

    int current_date = 1;
    int word_count = points[start_point];
    for (i = 0; i < word_count - 1; i++)
    {
        printf(" ");
    }
    while (current_date <= wan[month - 1])
    {
        if (word_count > 27)
        {
            printf("\n");
            word_count = 1;
        }

        if (search(word_count, 0) && current_date >= 1 && current_date <= 9)
        {
            printf("%d", current_date);
            current_date += 1;
        }
        else if (search(word_count, 1) && current_date >= 10)
        {
            printf("%d", current_date);
            current_date += 1;
            word_count += 1;
        }
        else
        {
            printf(" ");
        }
        word_count += 1;
    }
    printf("\n");
    return 0;
}
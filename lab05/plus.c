#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void reverse(char *str)
{
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++)
    {
        char ch = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = ch;
    }
}

char *addStrings(char *a, char *b)
{
    if (strlen(a) == 1 && strlen(b) == 1)
    {
        if (a[0] - '0' == 0 && b[0] - '0' == 0)
        {
            return "0";
        }
        else if (a[0] - '0' == 0 && b[0] - '0' != 0)
        {
            return b;
        }
        else if (a[0] - '0' != 0 && b[0] - '0' == 0)
        {
            return a;
        }
    }
    char *final = malloc(10001);
    char res[10001];
    memset(res, 0, 10001);
    int len_a = strlen(a);
    int len_b = strlen(b);
    int tempsum = 0;
    int temp_a = 0, temp_b = 0;
    int max_len = len_a > len_b ? len_a : len_b;
    for (int i = max_len - 1; i >= 0; i--)
    {
        if (len_a >= len_b)
        {
            if (i - abs(len_a - len_b) < 0)
            {
                temp_a = a[i] - '0';
                temp_b = 0;
            }
            else
            {
                temp_a = a[i] - '0';
                temp_b = b[i - abs(len_a - len_b)] - '0';
            }
        }
        else
        {
            if (i - abs(len_a - len_b) < 0)
            {
                temp_a = 0;
                temp_b = b[i] - '0';
            }
            else
            {
                temp_a = a[i - abs(len_a - len_b)] - '0';
                temp_b = b[i] - '0';
            }
        }
        tempsum = temp_a + temp_b;
        res[i] = tempsum + '0';
    }
    reverse(res);
    int add_more = 0;
    int carried = 0, carried_temp_x = 0, carried_temp_x1 = 0;
    int sum_len = strlen(res);
    for (int x = 0; x < sum_len; x++)
    {
        carried_temp_x = res[x] - '0';
        if (res[x + 1] == '\0')
        {
            carried_temp_x1 = 0;
        }
        else
        {
            carried_temp_x1 = res[x + 1] - '0';
        }
        if (carried_temp_x >= 10)
        {
            carried_temp_x1 += carried_temp_x / 10;
            carried_temp_x = carried_temp_x % 10;
            carried = 1;
        }
        else
        {
            carried = 0;
        }
        if (x + 1 >= sum_len)
        {
            add_more += 1;
        }
        if (x == sum_len - 1 && x + 1 == sum_len && carried == 0)
        {
            res[x] = carried_temp_x + '0';
        }
        else
        {
            res[x] = carried_temp_x + '0';
            res[x + 1] = carried_temp_x1 + '0';
        }
    }
    res[max_len + add_more] = '\0';
    reverse(res);
    int len_count = 1;
    int is_found_one = 0;
    for (int t = 0; t < max_len + add_more; t++)
    {
        if (isdigit(res[t]))
        {
            if ((res[t] - '0' == 0) && (is_found_one == 0))
            {
                continue;
            }
            else
            {
                is_found_one = 1;
                final[len_count - 1] = res[t];
                len_count += 1;
            }
        }
    }
    final[len_count - 1] = '\0';
    return final;
}

int main()
{
    char a[10001];
    char b[10001];
    scanf("%s", a);
    scanf("%s", b);
    printf("%s\n", addStrings(a, b));
    return 0;
}
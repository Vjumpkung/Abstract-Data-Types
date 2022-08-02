#include <stdio.h>
#include <math.h>

double distance(int *pos)
{
    return sqrt(pow(pos[0] - 0, 2) + pow(pos[1] - 0, 2));
}

int strlength(char *str)
{
    int i;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

int main()
{
    int arrsize = 0;
    scanf("%d", &arrsize);
    char str[100001];
    int i;
    int pos[2] = {0, 0};
    int move[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int mode = 0;
    scanf("%s", &str);
    int len = strlength(str);
    int temp_mode = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] == 'L')
        {
            temp_mode = mode + 1;
            if (temp_mode > 3)
            {
                mode = 0;
            }
            else
            {
                mode++;
            }
        }
        else if (str[i] == 'R')
        {
            temp_mode = mode - 1;
            if (temp_mode < 0)
            {
                mode = 3;
            }
            else
            {
                mode--;
            }
        }
        else if (str[i] == 'F')
        {
            pos[0] += move[mode][0];
            pos[1] += move[mode][1];
            // printf("%d %d %d\n", mode, move[mode][0], move[mode][1]);
        }
    }

    printf("%.4lf\n", distance(pos));

    return 0;
}
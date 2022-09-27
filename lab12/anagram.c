#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selectionSort(char *str, int arrSize)
{
    int i, j;
    for (i = 0; i < arrSize; i++)
    {
        int min_idx = i;
        char temp = str[i];
        for (j = i + 1; j < arrSize; j++)
        {
            if (str[j] < temp)
            {
                min_idx = j;
                temp = str[j];
            }
        }
        temp = str[i];
        str[i] = str[min_idx];
        str[min_idx] = temp;
    }
}

int isSame(char *s1, char *s2)
{
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    if (s1_len != s2_len)
    {
        return 0;
    }
    else
    {
        char *temp_s1 = (char *)malloc(sizeof(char) * (s1_len + 1));
        char *temp_s2 = (char *)malloc(sizeof(char) * (s2_len + 1));
        strcpy(temp_s1, s1);
        strcpy(temp_s2, s2);
        selectionSort(temp_s1, s1_len);
        selectionSort(temp_s2, s2_len);
        if (strcmp(temp_s1, temp_s2) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    int arrsize, round, i, j;
    scanf("%d %d", &arrsize, &round);
    char *inputt = (char *)malloc(sizeof(char *) * 51);
    char **ListStr = (char **)malloc(sizeof(char *) * arrsize);
    for (i = 0; i < arrsize; i++)
    {
        ListStr[i] = (char *)malloc(sizeof(char) * 51);
        scanf("%s", ListStr[i]);
    }
    for (i = 0; i < round; i++)
    {
        scanf("%s", inputt);
        for (j = 0; j < arrsize; j++)
        {
            if (isSame(inputt, ListStr[j]))
            {
                printf("%s ", ListStr[j]);
            }
        }
        printf("\n");
    }
    return 0;
}
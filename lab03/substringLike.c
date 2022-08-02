#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
18 3 0
acabababababcbabab
aba
*/

/*
15 4 2
AAAGTGTGTCTGATT
GTAT
*/

/*
18 3 1
acabababababcabbab
abc
*/

/*
18 3 1
acabababababcbabab
aba
*/

int main()
{
    int strSize, subLen, subDiff, i, j, k, l;
    scanf("%d %d %d", &strSize, &subLen, &subDiff);
    char *str = (char *)malloc(sizeof(char) * (strSize + 1));
    char *sub = (char *)malloc(sizeof(char) * (subLen + 1));
    scanf("%s", str);
    scanf("%s", sub);
    i = 0;
    while (i < strSize - subLen + 1)
    {
        char temptext[subLen];
        for (j = 0; j < subLen; j++)
        {
            temptext[j] = str[i + j];
            // printf("%c", str[i + j]);
        }
        temptext[j] = '\0';
        int diff = 0;
        int diff_idx[subLen];
        int already = 0;
        for (k = 0; k < subLen; k++)
        {
            // printf("%s %s %c %c ", temptext, sub, temptext[k], sub[k]);
            if (strcmp(temptext, sub) == 0)
            {
                printf("[");
                for (l = 0; l < subLen; l++)
                {
                    printf("%c", temptext[l]);
                }
                printf("]");
                i += subLen;
                already = 1;
                break;
            }
            else if (temptext[k] != sub[k])
            {
                diff_idx[k] = i + k;
                diff += 1;
            }
            else if (temptext[k] == sub[k])
            {
                diff_idx[k] = -1;
                continue;
            }
        }
        if (already)
        {
            continue;
        }
        // printf("%d\n", diff);
        if (diff <= subDiff && diff != 0)
        {
            printf("[");
            for (l = 0; l < subLen; l++)
            {
                // printf("%d ", diff_idx[l]);
                if (diff_idx[l] == -1)
                {
                    printf("%c", temptext[l]);
                }
                else
                {
                    printf("?");
                }
            }
            i += subLen;
            // printf("\n");
            printf("]");
            continue;
        }
        else
        {
            printf("%c", str[i]);
        }
        i++;
    }
    while (str[i] != '\0')
    {
        printf("%c", str[i]);
        i++;
    }
    printf("\n");
    free(sub);
    free(str);
    return 0;
}
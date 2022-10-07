#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int graph[10000][10000];
int maxx = 0;

unsigned long long int factorial_log[35];
unsigned long long int factorial(int n)
{
    long long temp = 1;
    if (factorial_log[n] != 0)
    {
        return factorial_log[n];
    }
    else
    {
        for (int i = n; i >= 1; i--)
        {
            temp = temp * i;
        }
    }
    factorial_log[n] = temp;
    return factorial_log[n];
}

long long int combinations(long int n, long int r)
{
    if (r == 0 || n == r)
    {
        return 1;
    }
    if (r > n / 2)
    {
        r = n - r;
    }
    if (r < n)
    {
        return combinations(n - 1, r) * (n) / (n - r);
    }
    unsigned long long temps = 1;
    int steps = 1;
    while (steps <= r)
    {
        temps *= n;
        steps += 1;
        n--;
    }
    return temps / factorial(r);
}

void GetLineSize(int **res, int *line, int lineSize, int n, int k, int *resLen, int idx)
{
    if (lineSize == k)
    {
        res[*resLen] = (int *)malloc(sizeof(int) * k);
        memcpy(res[*resLen], line, sizeof(int) * k);
        (*resLen) = (*resLen) + 1;
        return;
    }

    for (int i = idx; i <= n; i++)
    {
        line[lineSize] = i;
        GetLineSize(res, line, lineSize + 1, n, k, resLen, i + 1);
    }
}

int **combine(int n, int k, int *returnSize, int **returnColumnSizes)
{

    int **res = (int **)malloc(sizeof(int *) * 10000);
    int line[100];
    int lineSize = 0;
    int resLen = 0;
    GetLineSize(res, line, lineSize, n, k, &resLen, 1);
    *returnSize = resLen;
    *returnColumnSizes = malloc(sizeof(int) * (*returnSize));
    int i = *returnSize - 1;
    while (i >= 0)
    {
        (*returnColumnSizes)[i--] = k;
    }
    return res;
}

void add(int temp_from, int temp_to, int size)
{
    graph[temp_from][temp_to] = 1;
    graph[temp_to][temp_from] = 1;
}

void create_graph(int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                graph[i][j] = 1;
            }
            else
            {
                graph[i][j] = 0;
            }
        }
    }
}

void is_clique(int size)
{
    int n, r, i, j, k, N, R;
    N = size;
    for (R = 1; R < size; R++)
    {
        int comb = combinations(N, R);

        int **arr = (int **)malloc(N * sizeof(int *));
        for (i = 0; i < N; i++)
        {
            arr[i] = (int *)malloc(R * sizeof(int));
        }

        arr = combine(N, R, *arr, arr);

        int isClick = 1;

        for (i = 0; i < comb; i++)
        {
            isClick = 1;
            for (j = 0; j < R; j++)
            {
                for (k = 0; k < R; k++)
                {
                    if (graph[arr[i][j] - 1][arr[i][k] - 1] == 1)
                    {
                        continue;
                    }
                    else
                    {
                        isClick = 0;
                    }
                }
            }
            if (isClick)
            {
                if (R > maxx)
                {
                    maxx = R;
                }
            }
        }
    }
}

int main()
{
    int map_size, line, round, i, temp_from, temp_to, temp_weight, too, start;
    scanf("%d %d", &map_size, &line);
    create_graph(map_size);
    for (i = 0; i < line; i++)
    {
        scanf("%d %d", &temp_from, &temp_to);
        add(temp_from, temp_to, map_size);
    }
    is_clique(map_size);
    printf("%d\n", maxx);
    return 0;
}
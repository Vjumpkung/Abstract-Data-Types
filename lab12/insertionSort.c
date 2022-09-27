#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int arrSize)
{
    int i;
    for (i = 0; i < arrSize; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertion_sort(int *arr, int arrSize)
{
    int i, j, k, temp, insertIdx, find = 0, chain = 0;
    for (i = 1; i < arrSize; i++)
    {
        temp = arr[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (arr[i] < arr[j])
            {
                // printf("%d < %d\n", arr[i], arr[j]);
                find = 1;
                insertIdx = j;
                chain++;
            }
            else if (chain == 0)
            {
                find = 0;
                break;
            }
            else
            {
                break;
            }
        }
        chain = 0;
        if (find)
        {
            // printf("temp = %d insert pos = %d\n", temp, insertIdx);
            for (k = i - 1; k >= insertIdx; k--)
            {
                // printf("k+1 = %d , k = %d\n", k + 1, k);
                arr[k + 1] = arr[k];
            }
            arr[insertIdx] = temp;
        }
        print_array(arr, arrSize);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    insertion_sort(arr, n);
    return 0;
}
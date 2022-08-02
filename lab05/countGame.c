#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct list
{
    int *array;
    int count;
    int size;
} List;

int kINcount(int number, int k)
{
    while (number != 0)
    {
        if (number % 10 == k)
        {
            return 1;
        }
        number /= 10;
    }
    return 0;
}

void create(List *arr, int size)
{
    arr->array = (int *)malloc(sizeof(int) * size);
    arr->count = 0;
    arr->size = size;
}

void insert(List *arr, int index, int val)
{
    if (arr->count == arr->size)
    {
        printf("List Full\n");
        return;
    }
    if (index < 0 || index > arr->size - 1)
    {
        printf("IndexError : Index out of range\n");
        return;
    }
    if (index < arr->count)
    {
        int i;
        for (i = arr->count; i > index; i--)
        {
            arr->array[i] = arr->array[i - 1];
        }
        arr->array[index] = val;
    }
    else
    {
        arr->array[arr->count] = val;
    }
    arr->count++;
}

void delete (List *arr, int index)
{
    int i = 0;
    if (arr->count == 0)
    {
        printf("Empty List\n");
        return;
    }
    if (index < 0 || index > arr->size - 1)
    {
        printf("IndexError : Index out of range\n");
        return;
    }
    if (index < arr->count)
    {
        for (i = index; i < arr->count - 1; i++)
        {
            arr->array[i] = arr->array[i + 1];
        }
    }
    arr->count--;
}

int Get(List *arr, int idx)
{
    return arr->array[idx];
}

void Edit(List *arr, int idx, int new_val)
{
    arr->array[idx] = new_val;
}

void PrintList(List *arr)
{
    int i;
    for (i = 0; i < arr->count; i++)
    {
        printf("%d ", arr->array[i]);
    }
    printf("\n");
}

int main()
{
    List arr = {NULL, 0};
    List counter = {NULL, 0};
    List number = {NULL, 0};
    int n, k, i, x, c = 1;
    scanf("%d %d", &n, &k);
    create(&arr, n);
    create(&counter, n);
    create(&number, n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);
        insert(&arr, i, x);
        insert(&counter, i, 0);
        insert(&number, i, i + 1);
    }
    int idx = 0, temp;
    while (arr.count > 1)
    {
        if (c % k == 0 || kINcount(c, k))
        {
            temp = Get(&counter, idx) + 1;
            Edit(&counter, idx, temp);
        }
        if (Get(&counter, idx) > Get(&arr, idx))
        {
            delete (&arr, idx);
            delete (&counter, idx);
            delete (&number, idx);
            idx--;
        }
        if (idx + 1 >= arr.count)
        {
            idx = 0;
        }
        else
        {
            idx++;
        }
        c++;
    }
    PrintList(&number);
    return 0;
}
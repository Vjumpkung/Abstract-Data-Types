#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
    int *data;
    int last_index;
} heap_t;

heap_t *init_heap(int m)
{
    heap_t *temp = (heap_t *)malloc(sizeof(heap_t) * (m + 1));
    temp->data = (int *)malloc(sizeof(int) * (m + 1));
    temp->last_index = 0;
    return temp;
}

void insert(heap_t *max_heap, int data)
{
    max_heap->last_index++;
    int insert_pos = max_heap->last_index;
    max_heap->data[max_heap->last_index] = data;
    int parent = insert_pos / 2;
    int swap = 0;
    while (parent >= 1 && max_heap->data[parent] < max_heap->data[insert_pos])
    {
        // swap element
        swap = max_heap->data[parent];
        max_heap->data[parent] = max_heap->data[insert_pos];
        max_heap->data[insert_pos] = swap;

        insert_pos = parent;
        parent = parent / 2;
    }
}

void delete_max(heap_t *max_heap)
{
    max_heap->last_index--;
    max_heap->data[1] = max_heap->data[max_heap->last_index + 1];
    int idx = 1, child = 1, parent = 1, swap = 0;
    parent = idx;
    child = 2 * parent;
    while (1)
    {
        if (child <= max_heap->last_index && max_heap->data[parent] < max_heap->data[child])
        {
            // swap element
            swap = max_heap->data[parent];
            max_heap->data[parent] = max_heap->data[child];
            max_heap->data[child] = swap;
            parent = child;
            child = 2 * parent;
        }
        else if (child + 1 <= max_heap->last_index && max_heap->data[parent] < max_heap->data[child + 1])
        {
            // swap element
            swap = max_heap->data[parent];
            max_heap->data[parent] = max_heap->data[child + 1];
            max_heap->data[child + 1] = swap;
            parent = child + 1;
            child = 2 * parent;
        }
        else
        {
            break;
        }
    }
}

int find_max(heap_t *max_heap)
{
    if (max_heap->last_index <= 0)
    {
        return -1;
    }
    return max_heap->data[1];
}

void insert_special(heap_t *max_heap, int data, int old_idx)
{
    int insert_pos = old_idx;
    max_heap->data[old_idx] = data;
    int parent = insert_pos / 2;
    int swap = 0;
    while (parent >= 1 && max_heap->data[parent] < max_heap->data[insert_pos])
    {
        // swap element
        swap = max_heap->data[parent];
        max_heap->data[parent] = max_heap->data[insert_pos];
        max_heap->data[insert_pos] = swap;

        insert_pos = parent;
        parent = parent / 2;
    }
}

void update_key(heap_t *max_heap, int old, int new)
{
    int i;
    int old_index;
    for (i = 1; i < max_heap->last_index + 1; i++)
    {
        if (max_heap->data[i] == old)
        {
            old_index = i;
            break;
        }
    }
    insert_special(max_heap, new, old_index);
}

void bfs(heap_t *max_heap)
{
    int i;
    for (i = 1; i < max_heap->last_index + 1; i++)
    {
        printf("%d ", max_heap->data[i]);
    }
    printf("\n");
}

int main(void)
{
    heap_t *max_heap = NULL;
    int m, n, i;
    int command, data;
    int old_key, new_key;

    scanf("%d %d", &m, &n);
    max_heap = init_heap(m);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d", &data);
            insert(max_heap, data);
            break;
        case 2:
            delete_max(max_heap);
            break;
        case 3:
            printf("%d\n", find_max(max_heap));
            break;
        case 4:
            scanf("%d %d", &old_key, &new_key);
            update_key(max_heap, old_key, new_key);
            break;
        case 5:
            bfs(max_heap);
            break;
        }
    }
    return 0;
}
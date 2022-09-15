#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char text[16];
    int frequency;
    struct node *left;
    struct node *right;
} node_t;

typedef struct minHeap
{
    node_t **arr_node;
    int last_index;
} heap_t;

heap_t *create(int size)
{
    heap_t *temp = (heap_t *)malloc(sizeof(heap_t));
    temp->arr_node = (node_t **)malloc(sizeof(node_t) * (size + 1));
    temp->last_index = 0;
    return temp;
}

void insert(heap_t *minHeap, node_t *newNode)
{
    minHeap->last_index++;
    int insert_pos = minHeap->last_index;
    minHeap->arr_node[minHeap->last_index] = newNode;
    int parent = insert_pos / 2;
    node_t *swap = NULL;
    while (parent >= 1 && minHeap->arr_node[parent]->frequency > minHeap->arr_node[insert_pos]->frequency)
    {
        // swap element
        swap = minHeap->arr_node[parent];
        minHeap->arr_node[parent] = minHeap->arr_node[insert_pos];
        minHeap->arr_node[insert_pos] = swap;

        insert_pos = parent;
        parent /= 2;
    }
}

node_t *delete (heap_t *minHeap)
{
    minHeap->last_index--;
    node_t *temp_node = minHeap->arr_node[1];
    minHeap->arr_node[1] = minHeap->arr_node[minHeap->last_index + 1];
    int parent = 1;
    node_t *swap = NULL;
    int child_l = 2 * parent, childe_r = 2 * parent + 1;
    while (parent <= minHeap->last_index && ((childe_r <= minHeap->last_index && minHeap->arr_node[parent]->frequency > minHeap->arr_node[childe_r]->frequency) || (child_l <= minHeap->last_index && minHeap->arr_node[parent]->frequency > minHeap->arr_node[child_l]->frequency)))
    {
        if (minHeap->arr_node[child_l]->frequency > minHeap->arr_node[childe_r]->frequency)
        {
            swap = minHeap->arr_node[childe_r];
            minHeap->arr_node[childe_r] = minHeap->arr_node[parent];
            minHeap->arr_node[parent] = swap;
            parent = childe_r;
        }
        else
        {
            swap = minHeap->arr_node[child_l];
            minHeap->arr_node[child_l] = minHeap->arr_node[parent];
            minHeap->arr_node[parent] = swap;
            parent = child_l;
        }
        child_l = 2 * parent, childe_r = 2 * parent + 1;
    }
    return temp_node;
}

void print_array(int *arr, int arrSize)
{
    int i;
    for (i = 0; i < arrSize; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}

void print_huffman(node_t *bintree, int *arr, int arrSize)
{
    if (bintree->left != NULL)
    {
        arr[arrSize] = 0;
        print_huffman(bintree->left, arr, arrSize + 1);
    }
    if (bintree->right != NULL)
    {
        arr[arrSize] = 1;
        print_huffman(bintree->right, arr, arrSize + 1);
    }
    if (strcmp("Nothing", bintree->text) != 0)
    {
        printf("%s: ", bintree->text);
        print_array(arr, arrSize);
    }
}

int main()
{
    heap_t *test = NULL;
    int n, i;
    scanf("%d", &n);
    test = create(n);
    for (i = 1; i <= n; i++)
    {
        node_t *temp2 = (node_t *)malloc(sizeof(node_t));
        scanf("%s %d", temp2->text, &temp2->frequency);
        temp2->left = NULL;
        temp2->right = NULL;
        insert(test, temp2);
    }
    node_t *n_left = NULL;
    node_t *n_right = NULL;
    node_t *new = NULL;
    while (test->last_index > 1)
    {
        n_left = delete (test);
        n_right = delete (test);
        new = (node_t *)malloc(sizeof(node_t));
        strcpy(new->text, "Nothing");
        new->left = n_left;
        new->right = n_right;
        new->frequency = n_left->frequency + n_right->frequency;
        insert(test, new);
    }
    int arr[15];
    print_huffman(test->arr_node[1], arr, 0);
    return 0;
}
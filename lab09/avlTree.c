#include "week9.h"
#include <stdio.h>
#include <stdlib.h>
// #include <week9.h> //for hw-send only

#ifndef __avl_tree__
typedef struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
} node_t;

typedef node_t avl_t;
#endif

avl_t *insert(avl_t *t, int data)
{
    return t;
}

avl_t *delete (avl_t *t, int data)
{
    return t;
}

int main(void)
{
    avl_t *t = NULL;
    int n, i;
    int command, data;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d", &data);
            t = insert(t, data);
            break;
        case 2:
            scanf("%d", &data);
            t = delete (t, data);
            break;
        case 3:
            print_tree(t);
            break;
        }
    }
    return 0;
}
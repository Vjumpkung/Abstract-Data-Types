#include "week8.h"
#include <stdio.h>
#include <stdlib.h>
// #include <week8.h> //for hw-send only

#ifndef __bin_tree__
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node_t;

typedef node_t tree_t;
#endif

void print_preorder1(tree_t *t)
{
    if (t == NULL)
    {
        return;
    }
    printf("%d ", t->data);
    print_preorder1(t->left);
    print_preorder1(t->right);
}

void print_preorder(tree_t *t)
{
    print_preorder1(t);
    printf("\n");
}

void print_postorder1(tree_t *t)
{
    if (t == NULL)
    {
        return;
    }
    print_postorder1(t->left);
    print_postorder1(t->right);
    printf("%d ", t->data);
}

void print_postorder(tree_t *t)
{
    print_postorder1(t);
    printf("\n");
}

void print_inorder1(tree_t *t)
{
    if (t == NULL)
    {
        return;
    }
    print_inorder1(t->left);
    printf("%d ", t->data);
    print_inorder1(t->right);
}

void print_inorder(tree_t *t)
{
    print_inorder1(t);
    printf("\n");
}

int main(void)
{
    tree_t *t = NULL;
    int n, i;
    int parent, child;
    int branch; // 0 root, 1 left, 2 right

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d %d %d", &parent, &child, &branch);
        t = attach(t, parent, child, branch);
    }

    print_preorder(t);
    print_postorder(t);
    print_inorder(t);

    return 0;
}
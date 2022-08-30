#include "week8.h"
#include <stdio.h>
#include <stdlib.h>
// #include <week8.h> //for hw-send only

// PPP-PP-P--PPP--PP-P-
// PPPPPP-P--PPPP-PP-P-

#ifndef __bin_tree__
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node_t;

typedef node_t tree_t;
#endif

typedef struct stack
{
    int data;
    struct stack *next;
} Stack;

void push(Stack **s, int val)
{
    Stack *temp = (Stack *)malloc(sizeof(Stack));
    temp->data = val;
    temp->next = NULL;

    temp->next = *s;
    *s = temp;
}

void pop(Stack **s)
{
    if (*s == NULL)
    {
        return;
    }
    Stack *temp = *s;
    *s = (*s)->next;
    free(temp);
}

int top(Stack **s)
{
    return (*s)->data;
}

void print_stack(Stack **s)
{
    while (*s != NULL)
    {
        printf("%d->", (*s)->data);
        (*s) = (*s)->next;
    }
    printf("\n");
}

int isEmpty(Stack **s)
{
    if (*s == NULL)
    {
        return 1;
    }
    return 0;
}

int is_full(tree_t *t)
{
    if (t == NULL)
    {
        return 1;
    }
    if (t->left == NULL && t->right == NULL)
    {
        return 1;
    }
    if (t->left != NULL && t->right != NULL)
    {
        return is_full(t->left) && is_full(t->right);
    }
    return 0;
}

Stack *s = NULL;

void checkDepth(tree_t *t, int depth)
{
    if (t->left == NULL || t->right == NULL)
    {
        push(&s, depth);
        return;
    }
    if (t->left != NULL)
    {
        checkDepth(t->left, depth + 1);
    }
    if (t->right != NULL)
    {
        checkDepth(t->right, depth + 1);
    }
}

int is_perfect(tree_t *t)
{
    checkDepth(t, 0);
    int is_height_equal = 1;
    int before = top(&s);
    int current = 0;
    while (!isEmpty(&s))
    {
        current = top(&s);
        if (current == before)
        {
            pop(&s);
            before = current;
        }
        else
        {
            is_height_equal = 0;
            while (!isEmpty(&s))
            {
                pop(&s);
            }
            s = NULL;
            break;
        }
    }
    if (is_height_equal && is_full(t))
    {
        return 1;
    }
    return 0;
}

int size(tree_t *t)
{
    if (t == NULL)
    {
        return 0;
    }
    return size(t->left) + size(t->right) + 1;
}

int completed(tree_t *t, int idx, int t_size)
{
    if (t == NULL)
    {
        return 1;
    }
    if (idx >= t_size)
    {
        return 0;
    }
    return completed(t->left, 2 * idx + 1, t_size) && completed(t->right, 2 * idx + 2, t_size);
}

int is_complete(tree_t *t)
{
    int idx = 0;
    int no_node = size(t);
    return completed(t, idx, no_node);
}

int is_degenerate(tree_t *t)
{
    if (t == NULL || (t->left == NULL && t->right == NULL))
    {
        return 1;
    }
    if (t->left != NULL && t->right == NULL)
    {
        is_degenerate(t->left);
    }
    if (t->right != NULL && t->left == NULL)
    {
        is_degenerate(t->right);
    }
    if (t->left != NULL && t->right != NULL)
    {
        return 0;
    }
    return 1;
}

int left = 0;
int right = 0;

int is_skewed(tree_t *t)
{
    // printf("%p l=%p r=%p l=%d r=%d\n", t, t->left, t->right, left, right);
    if (t == NULL || (t->left == NULL && t->right == NULL))
    {
        return 1;
    }

    if (t->left != NULL && t->right != NULL)
    {
        return 0;
    }
    if (t->left != NULL && right != 1)
    {
        left = 1;
        return is_skewed(t->left);
    }
    if (t->right != NULL && left != 1)
    {
        right = 1;
        return is_skewed(t->right);
    }
    return 0;
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

    printf("%d %d %d %d %d\n", is_full(t), is_perfect(t), is_complete(t), is_degenerate(t), is_skewed(t));

    return 0;
}
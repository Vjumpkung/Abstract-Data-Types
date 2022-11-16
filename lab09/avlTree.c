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

int max(int x, int y)
{
    return x > y ? x : y;
}

int height(avl_t *t)
{
    if (t == NULL)
    {
        return 0;
    }
    return max(height(t->left), height(t->right)) + 1;
}

int balanceFactor(avl_t *t)
{
    if (t == NULL)
    {
        return 0;
    }
    return height(t->left) - height(t->right);
}

avl_t *RotateLeft(avl_t *a)
{
    avl_t *b = a->right;
    avl_t *new_head_left = b->left;
    b->left = a;
    a->right = new_head_left;
    a->height = height(a);
    b->height = height(b);
    return b;
}

avl_t *RotateRight(avl_t *b)
{
    avl_t *a = b->left;
    avl_t *new_head_right = a->right;
    a->right = b;
    b->left = new_head_right;
    b->height = height(b);
    a->height = height(a);
    return a;
}

avl_t *create(int data)
{
    avl_t *Node = (avl_t *)malloc(sizeof(node_t));
    Node->data = data;
    Node->height = 0;
    Node->left = NULL;
    Node->right = NULL;
    return Node;
}

avl_t *insert(avl_t *t, int data)
{
    if (t == NULL)
    {
        return create(data);
    }
    if (data < t->data)
    {
        t->left = insert(t->left, data);
    }
    else if (data > t->data)
    {
        t->right = insert(t->right, data);
    }
    else
    {
        return t;
    }
    t->height = height(t);
    int balance = balanceFactor(t);
    if (balance > 1)
    {
        if (data < t->left->data)
        {
            return RotateRight(t);
        }
        if (data > t->left->data)
        {
            t->left = RotateLeft(t->left);
            return RotateRight(t);
        }
    }
    if (balance < -1)
    {
        if (data > t->right->data)
        {
            return RotateLeft(t);
        }
        if (data < t->right->data)
        {
            t->right = RotateRight(t->right);
            return RotateLeft(t);
        }
    }
    return t;
}

avl_t *find_min(avl_t *t)
{
    avl_t *current = t;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

avl_t *delete (avl_t *t, int data)
{
    if (t == NULL)
    {
        return t;
    }
    if (data < t->data)
    {
        t->left = delete (t->left, data);
    }
    else if (data > t->data)
    {
        t->right = delete (t->right, data);
    }
    else
    {
        if (t->left == NULL || t->right == NULL)
        {
            avl_t *temp = t->left ? t->left : t->right;
            if (temp == NULL)
            {
                temp = t;
                t = NULL;
            }
            else
            {
                *t = *temp;
            }
            free(temp);
        }
        else
        {
            avl_t *temp = find_min(t->right);
            t->data = temp->data;
            t->right = delete (t->right, temp->data);
        }
    }

    if (t == NULL)
    {
        return t;
    }
    t->height = height(t);
    int balance = balanceFactor(t);
    if (balance > 1)
    {
        if (data > t->left->data)
        {
            return RotateRight(t);
        }
        if (data < t->left->data)
        {
            t->left = RotateLeft(t->left);
            return RotateRight(t);
        }
    }
    if (balance < -1)
    {
        if (data < t->right->data)
        {
            return RotateLeft(t);
        }
        if (data > t->right->data)
        {
            t->right = RotateRight(t->right);
            return RotateLeft(t);
        }
    }
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
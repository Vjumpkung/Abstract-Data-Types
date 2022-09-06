#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node_t;

typedef node_t bst_t;
typedef bst_t bst;

int find_min(bst_t *t)
{
    int val = 0;
    while (1)
    {
        if (t->left == NULL)
        {
            val = t->data;
            break;
        }
        t = t->left;
    }
    return val;
}

int find_max(bst_t *t)
{
    int val;
    while (1)
    {
        if (t->right == NULL)
        {
            val = t->data;
            break;
        }
        t = t->right;
    }
    return val;
}

bst_t *search(bst_t *t, int data)
{
    if (t == NULL)
    {
        return t;
    }
    if (t->data == data)
    {
        return t;
    }
    else
    {
        if (t->data > data)
        {
            return search(t->left, data);
        }
        else
        {
            return search(t->right, data);
        }
    }
}

int l = 0;
int r = 0;

bst_t *search_before(bst_t *target, bst_t *t)
{
    if (target == t)
    {
        return t;
    }
    if (t->left == target)
    {
        l = 1;
        r = 0;
        return t;
    }
    else if (t->right == target)
    {
        l = 0;
        r = 1;
        return t;
    }
    else
    {
        if (target->data > t->data)
        {
            return search_before(target, t->right);
        }
        else
        {
            return search_before(target, t->left);
        }
    }
}

bst_t *delete (bst_t *t, int data)
{
    bst_t *del_ptr = search(t, data);
    bst_t *bef = NULL;
    bef = search_before(del_ptr, t);
    int cases = 0;
    if (del_ptr->left == NULL && del_ptr->right == NULL && del_ptr != bef) // case 1
    {
        cases = 1;
        if (l)
        {
            bef->left = NULL;
        }
        if (r)
        {
            bef->right = NULL;
        }
    }

    else if (del_ptr->left != NULL && del_ptr->right == NULL && del_ptr != bef) // case 2.1
    {
        cases = 2;
        if (l)
        {
            bef->left = del_ptr->left;
        }
        if (r)
        {
            bef->right = del_ptr->left;
        }
    }

    else if (del_ptr->right != NULL && del_ptr->left == NULL && del_ptr != bef) // case 2.2
    {
        cases = 2;
        if (l)
        {
            bef->left = del_ptr->right;
        }
        if (r)
        {
            bef->right = del_ptr->right;
        }
    }
    else if (del_ptr->right != NULL && del_ptr->left != NULL) // case 3
    {
        cases = 3;
        int new_head = find_min(del_ptr->right);
        bst_t *new_head_ptr = search(del_ptr->right, new_head);
        bst_t *before_new_head = search_before(new_head_ptr, del_ptr);
        before_new_head = delete (before_new_head, new_head);
        del_ptr->data = new_head;
    }
    if (cases != 3)
    {
        free(del_ptr);
    }
    l = 0;
    r = 0;
    return t;
}

int find(bst_t *t, int data)
{
    if (t == NULL)
    {
        return 0;
    }
    if (t->data == data)
    {
        return 1;
    }
    else
    {
        if (t->data > data)
        {
            return find(t->left, data);
        }
        else
        {
            return find(t->right, data);
        }
    }
}

bst *insert(bst *tree, int val)
{
    if (find(tree, val))
    {
        return tree;
    }
    bst *temp = (bst *)malloc(sizeof(bst));
    bst *tree_ptr = tree;
    temp->data = val;
    temp->right = NULL;
    temp->left = NULL;
    if (tree == NULL)
    {
        return temp;
    }
    while (1)
    {
        if (tree_ptr->right != NULL && temp->data > tree_ptr->data)
        {
            tree_ptr = tree_ptr->right;
        }
        if (tree_ptr->left != NULL && temp->data < tree_ptr->data)
        {
            tree_ptr = tree_ptr->left;
        }
        if (tree_ptr->left == NULL && temp->data < tree_ptr->data)
        {
            tree_ptr->left = temp;
            break;
        }
        if (tree_ptr->right == NULL && temp->data > tree_ptr->data)
        {
            tree_ptr->right = temp;
            break;
        }
    }
    return tree;
}

int main(void)
{
    bst_t *t = NULL;
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
            scanf("%d", &data);
            printf("%d\n", find(t, data));
            break;
        case 4:
            printf("%d\n", find_min(t));
            break;
        case 5:
            printf("%d\n", find_max(t));
            break;
        }
    }
    return 0;
}
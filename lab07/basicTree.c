#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *right;
    struct node *down;
} node_t;
typedef node_t tree_t;

tree_t *find(tree_t *t, int v)
{
    if (t == NULL)
    {
        return t;
    }
    if (t->data == v)
    {
        return t;
    }
    tree_t *pos = find(t->down, v);
    if (pos != NULL)
    {
        return pos;
    }
    else
    {
        return find(t->right, v);
    }
}

tree_t *find_delete(tree_t *t, tree_t *par)
{
    if (t == NULL)
    {
        return t;
    }
    if (t->down == par)
    {
        return t;
    }
    if (t->right == par)
    {
        return t;
    }
    tree_t *pos = find_delete(t->down, par);
    if (pos != NULL)
    {
        return pos;
    }
    else
    {
        return find_delete(t->right, par);
    }
}

int search(tree_t *t, int node)
{
    if (find(t, node) != NULL)
    {
        return 1;
    }
    return 0;
}

tree_t *attach(tree_t *t, int parent, int child)
{
    tree_t *temp = (tree_t *)malloc(sizeof(tree_t));
    tree_t *pos = find(t, parent);
    temp->data = child;
    temp->down = NULL;
    temp->right = NULL;
    if (t == NULL)
    {
        tree_t *head = (tree_t *)malloc(sizeof(tree_t));
        head->data = parent;
        head->down = temp;
        head->right = NULL;
        return head->down;
    }
    if (pos->down == NULL)
    {
        pos->down = temp;
    }
    else
    {
        pos = pos->down;
        while (pos->right != NULL)
        {
            pos = pos->right;
        }
        pos->right = temp;
    }
    return t;
}

tree_t *detach(tree_t *t, int node)
{
    tree_t *temp = find(t, node);
    tree_t *pos = find_delete(t, temp);
    pos->down = NULL;
    pos->right = NULL;
    free(temp);
    return t;
}

int degree(tree_t *t, int node)
{
    int c = 0;
    tree_t *pos = find(t, node);
    pos = pos->down;
    while (pos != NULL)
    {
        c++;
        pos = pos->right;
    }
    return c;
}

int is_root(tree_t *t, int node)
{
    return (t->data == node) ? 1 : 0;
}

int is_leaf(tree_t *t, int node)
{
    return (find(t, node)->down == NULL) ? 1 : 0;
}

int depth(tree_t *t, int node)
{
    if (t == NULL)
    {
        return -1;
    }

    int dist = -1;

    if ((t->data == node) || ((dist = depth(t->down, node)) >= 0))
    {
        return dist + 1;
    }
    else
    {
        dist = depth(t->right, node);
    }
    return dist;
}

void siblings(tree_t *t, int node)
{
    tree_t *temp = find(t, node);
    tree_t *pos = find_delete(t, temp);
    if (is_root(t, node))
    {
        printf("\n");
        return;
    }
    if (pos->down != NULL)
    {
        pos = pos->down;
    }
    else
    {
        pos = pos->right;
    }
    while (pos != NULL)
    {
        if (node != pos->data)
        {
            printf("%d ", pos->data);
        }
        pos = pos->right;
    }
    printf("\n");
}

void bfs(tree_t *t)
{
}

void pdfs(tree_t *t)
{
    if (t == NULL)
    {
        return;
    }
    int i;
    printf("%d ", t->data);
    pdfs(t->down);
    pdfs(t->right);
}

void dfs(tree_t *t)
{
    pdfs(t);
    printf("\n");
}

void space_print(tree_t *t, int space)
{
    if (t == NULL)
    {
        return;
    }
    int i;
    for (i = 0; i < space; i++)
    {
        printf(" ");
    }
    printf("%d\n", t->data);
    space_print(t->down, space + 4);
    space_print(t->right, space);
}

void print_tree(tree_t *t)
{
    space_print(t, 0);
}

int main(void)
{
    tree_t *t = NULL;
    int n, i, command;
    int parent, child, node, start, end;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d %d", &parent, &child);
            t = attach(t, parent, child);
            break;
        case 2:
            scanf("%d", &node);
            t = detach(t, node);
            break;
        case 3:
            scanf("%d", &node);
            printf("%d\n", search(t, node));
            break;
        case 4:
            scanf("%d", &node);
            printf("%d\n", degree(t, node));
            break;
        case 5:
            scanf("%d", &node);
            printf("%d\n", is_root(t, node));
            break;
        case 6:
            scanf("%d", &node);
            printf("%d\n", is_leaf(t, node));
            break;
        case 7:
            scanf("%d", &node);
            siblings(t, node);
            break;
        case 8:
            scanf("%d", &node);
            printf("%d\n", depth(t, node));
            break;
        // case 9:
        //     scanf("%d %d", &start, &end);
        //     print_path(t, start, end);
        //     break;
        // case 10:
        //     scanf("%d %d", &start, &end);
        //     printf("%d\n", path_length(t, start, end));
        //     break;
        // case 11:
        //     scanf("%d", &node);
        //     ancestor(t, node);
        //     break;
        // case 12:
        //     scanf("%d", &node);
        //     descendant(t, node);
        //     break;
        case 13:
            bfs(t);
            break;
        case 14:
            dfs(t);
            break;
        case 15:
            print_tree(t);
            break;
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *right;
    struct node *down;
} node_t;
typedef node_t tree_t;

typedef struct stack
{
    int data;
    struct stack *next;
} Stack;

typedef struct Q
{
    int data;
    int depth;
    struct Q *next;
} Qnode_t;

typedef Qnode_t queue_t;

queue_t *enqueue(queue_t *q, int val, int dep)
{
    Qnode_t *temp = (Qnode_t *)malloc(sizeof(Qnode_t));
    temp->data = val;
    temp->depth = dep;
    temp->next = NULL;

    if (q == NULL)
    {
        temp->next = q;
        q = temp;
        return q;
    }
    else
    {
        Qnode_t *ptr = q;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
    return q;
}

queue_t *dequeue(queue_t *q)
{
    Qnode_t *temp = q;
    if (q == NULL)
    {
        printf("Queue is empty.\n");
        free(temp);
        return q;
    }
    if (q->next == NULL)
    {
        q = NULL;
    }
    else
    {
        q = q->next;
    }
    printf("%d\n", temp->data);
    free(temp);
    return q;
}

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

int isEmpty(Stack **s)
{
    if (*s == NULL)
    {
        return 1;
    }
    return 0;
}

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

int dow = 0;

tree_t *find_delete(tree_t *t, tree_t *par)
{
    if (t == NULL)
    {
        return t;
    }
    if (t->down == par)
    {
        dow = 1;
        return t;
    }
    if (t->right == par)
    {
        dow = 0;
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
    if (t->data == node)
    {
        t = NULL;
        return t;
    }
    tree_t *temp = find(t, node);
    tree_t *pos = find_delete(t, temp);
    if (dow)
    {
        pos->down = pos->down->right;
    }
    else
    {
        pos->right = pos->right->right;
    }
    dow = 0;
    free(temp);
    return t;
}

int degree(tree_t *t, int node)
{
    if (t == NULL)
    {
        return 0;
    }
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
    if (t == NULL)
    {
        return 0;
    }
    return (t->data == node) ? 1 : 0;
}

int is_leaf(tree_t *t, int node)
{
    if (t == NULL)
    {
        return 0;
    }
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

tree_t *find_head(tree_t *t, int val)
{
    tree_t *temp = t;
    while (temp != NULL)
    {
        if (temp->data == val)
        {
            return t;
        }
        else
        {
            tree_t *temp_head = find_head(temp->down, val);
            if (temp_head != NULL)
            {
                return temp_head;
            }
        }
        temp = temp->right;
    }
}

void siblings(tree_t *t, int node)
{
    tree_t *head = find_head(t, node);
    while (head != NULL)
    {
        if (head->data != node)
        {
            printf("%d ", head->data);
        }
        head = head->right;
    }
    printf("\n");
}

Stack *s = NULL;

int find_path(tree_t *start, tree_t *stop)
{
    if (start == stop)
    {
        push(&s, start->data);
        return 1;
    }
    if (start->down != NULL)
    {
        if (find_path(start->down, stop))
        {
            push(&s, start->data);
            return 1;
        }
    }
    if (start->right != NULL)
    {
        if (find_path(start->right, stop))
        {
            return 1;
        }
    }
    pop(&s);
    return 0;
}

void print_path(tree_t *t, int start, int stop)
{
    if (t == NULL)
    {
        return;
    }
    tree_t *started = find(t, start);
    tree_t *stopped = find(t, stop);
    find_path(started, stopped);
    while (!isEmpty(&s))
    {
        printf("%d ", top(&s));
        pop(&s);
    }
    s = NULL;
    printf("\n");
}

int path_length(tree_t *t, int start, int stop)
{
    if (t == NULL)
    {
        return 0;
    }
    tree_t *started = find(t, start);
    tree_t *stopped = find(t, stop);
    find_path(started, stopped);
    int c = 0;
    while (!isEmpty(&s))
    {
        c++;
        pop(&s);
    }
    s = NULL;
    return c;
}

void ancestor(tree_t *t, int node)
{
    if (t == NULL)
    {
        return;
    }
    tree_t *started = find(t, 1);
    tree_t *stopped = find(t, node);
    find_path(started, stopped);
    while (!isEmpty(&s))
    {
        printf("%d ", top(&s));
        pop(&s);
    }
    printf("\n");
}

queue_t *train = NULL;

void pdfs(tree_t *t, int isprint, tree_t *original)
{
    if (t == NULL)
    {
        return;
    }
    int i;
    if (isprint)
    {
        printf("%d ", t->data);
    }
    else
    {
        train = enqueue(train, t->data, depth(original, t->data));
    }
    pdfs(t->down, isprint, original);
    pdfs(t->right, isprint, original);
}

void bfs(tree_t *t)
{
    if (t == NULL)
    {
        return;
    }
    pdfs(t, 0, t);
    queue_t *temp = train;
    int max_depth = -1;
    while (temp != NULL)
    {
        if (temp->depth > max_depth)
        {
            max_depth = temp->depth;
        }
        temp = temp->next;
    }
    temp = train;
    int i = 0;
    for (i = 0; i <= max_depth; i++)
    {
        temp = train;
        while (temp != NULL)
        {
            if (temp->depth == i)
            {
                printf("%d ", temp->data);
            }
            temp = temp->next;
        }
    }
    train = NULL;
    printf("\n");
}

void descendant(tree_t *t, int node)
{
    if (t == NULL)
    {
        return;
    }
    tree_t *start = find(t, node);
    printf("%d ", node);
    start = start->down;
    pdfs(start, 0, start);
    queue_t *temp = train;
    int max_depth = -1;
    while (temp != NULL)
    {
        if (temp->depth > max_depth)
        {
            max_depth = temp->depth;
        }
        temp = temp->next;
    }
    temp = train;
    int i = 0;
    for (i = 0; i <= max_depth; i++)
    {
        temp = train;
        while (temp != NULL)
        {
            if (temp->depth == i)
            {
                printf("%d ", temp->data);
            }
            temp = temp->next;
        }
    }
    train = NULL;
    printf("\n");
}

void dfs(tree_t *t)
{
    if (t == NULL)
    {
        return;
    }
    pdfs(t, 1, t);
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
        case 9:
            scanf("%d %d", &start, &end);
            print_path(t, start, end);
            break;
        case 10:
            scanf("%d %d", &start, &end);
            printf("%d\n", path_length(t, start, end));
            break;
        case 11:
            scanf("%d", &node);
            ancestor(t, node);
            break;
        case 12:
            scanf("%d", &node);
            descendant(t, node);
            break;
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
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;

struct node *insertionSortList(struct node *head)
{
    struct node *minAd = NULL;
    struct node *firstloop = head;
    struct node *secondloop = head;
    int minn = 999999999;
    int tmp = 0;

    while (firstloop != NULL)
    {
        minn = firstloop->data;
        minAd = firstloop;
        while (secondloop != NULL)
        {
            if (secondloop->next != NULL && secondloop->next->data < minn)
            {
                minAd = secondloop->next;
                minn = secondloop->next->data;
            }
            secondloop = secondloop->next;
        }
        if (minAd != firstloop)
        {
            tmp = minAd->data;
            minAd->data = firstloop->data;
            firstloop->data = tmp;
        }
        firstloop = firstloop->next;
        secondloop = firstloop;
    }
    return head;
}

struct node *append(struct node *List, int val)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = NULL;
    if (List == NULL)
    {
        List = temp;
    }
    else
    {
        struct node *ptr = List;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
    return List;
}

void print_linked_list(struct node *List)
{
    while (List != NULL)
    {
        printf("%d ", List->data);
        List = List->next;
    }
    printf("\n");
}

int ListSize(struct node *List)
{
    int c = 0;
    while (List != NULL)
    {
        c++;
        List = List->next;
    }
    return c;
}

int find(struct node *q, int val)
{
    while (q != NULL)
    {
        if (q->data == val)
        {
            return 1;
        }
        q = q->next;
    }
    return 0;
}

typedef struct stack
{
    int data;
    struct stack *next;
} stack_t;

int scan(stack_t *q, int val)
{
    while (q != NULL)
    {
        if (q->data == val)
        {
            return 1;
        }
        q = q->next;
    }
    return 0;
}

stack_t *pop(stack_t *s)
{
    if (s == NULL)
    {
        return s;
    }
    stack_t *temp = s;
    s = (s)->next;
    free(temp);
    return s;
}

stack_t *push(stack_t *s, int val)
{
    stack_t *temp = (stack_t *)malloc(sizeof(stack_t));
    temp->data = val;
    temp->next = NULL;

    temp->next = s;
    s = temp;
    return s;
}

int top(stack_t *s)
{
    if (s == NULL)
    {
        return -1;
    }
    return s->data;
}

int graph[10000][10000];
int vertex_in[10000][2];
int graph_T[10000][10000];

stack_t *visited = NULL;
stack_t *S = NULL;
node_t *ans[100];

int t = 1;
int cursor = 0;

void dfs(int size, int start, int mode)
{
    if (vertex_in[start][0] == 0)
    {
        vertex_in[start][0] = t;
        t++;
    }
    else if (mode == 1)
    {
        ans[cursor] = append(ans[cursor], start);
    }
    int i = start, j;
    if (!scan(visited, start))
    {
        visited = push(visited, start);
    }

    for (j = 0; j < size; j++)
    {
        if (graph[i][j] == 1 || graph_T[i][j] == 1)
        {
            if (!scan(visited, j))
            {
                if (mode == 0)
                {
                    dfs(size, j, 0);
                }
                else if (mode == 1)
                {
                    dfs(size, j, 1);
                }
            }
        }
    }

    if (!scan(S, start))
    {
        S = push(S, start);
    }
    if (vertex_in[start][1] == 0)
    {
        vertex_in[start][1] = t;
        t++;
    }
}

void create_graph(int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            graph[i][j] = 0;
            graph_T[i][j] = 0;
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            vertex_in[i][j] = 0;
        }
    }
}

void transpose(int size)
{
    int i, j, temp;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            graph_T[i][j] = graph[j][i];
            graph[j][i] = 0;
        }
    }
}

void add(int temp_from, int temp_to, int size)
{
    graph[temp_from][temp_to] = 1;
}

int main()
{
    int map_size, line, round, i, temp_from, temp_to, q;
    for (q = 0; q < 100; q++)
    {
        ans[q] = (struct node *)malloc(sizeof(struct node));
        ans[q] = NULL;
    }
    scanf("%d %d", &map_size, &line);
    create_graph(map_size);
    for (i = 0; i < line; i++)
    {
        scanf("%d %d", &temp_from, &temp_to);
        add(temp_from, temp_to, map_size);
    }
    for (i = 0; i < map_size; i++)
    {
        dfs(map_size, i, 0);
    }
    visited = NULL;
    transpose(map_size);
    while (S != NULL)
    {
        int topp = top(S);
        dfs(map_size, topp, 1);
        S = pop(S);
        cursor++;
    }
    int r = 0;
    int longest = -1;
    int longest_idx = 0;
    while (ans[r] != NULL)
    {
        struct node *tempp = ans[r];
        int sizeee = ListSize(tempp);
        if (sizeee >= longest)
        {
            longest = sizeee;
            longest_idx = r;
        }
        r++;
    }
    print_linked_list(insertionSortList(ans[longest_idx]));
    return 0;
}
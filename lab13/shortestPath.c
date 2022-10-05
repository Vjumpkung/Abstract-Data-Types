#include <stdio.h>
#include <stdlib.h>

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

typedef struct node
{
    int number;
    int weight;
    struct node *next;
} List;

typedef struct vertex
{
    List **NodeArr;
    int size;
} Graph;

struct node *append(struct node *List, int val, int weight)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->number = val;
    temp->weight = weight;
    temp->next = NULL;
    if (List == NULL)
    {
        return temp;
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

Graph *create_graph(int size)
{
    int i;
    Graph *map = (Graph *)malloc(sizeof(Graph *));
    map->NodeArr = (List **)malloc(sizeof(List *) * size);
    map->size = size;
    for (i = 0; i < size; i++)
    {
        map->NodeArr[i] = (List *)malloc(sizeof(List));
        map->NodeArr[i] = NULL;
        map->NodeArr[i] = append(map->NodeArr[i], i, 0);
    }
    return map;
}

Graph *add(Graph *map, int from, int too, int weight)
{
    map->NodeArr[from] = append(map->NodeArr[from], too, weight);
    map->NodeArr[too] = append(map->NodeArr[too], from, weight);
    return map;
}

stack_t *already = NULL;
stack_t *energy = NULL;
stack_t *total = NULL;

int shortest_path(Graph *map, int from, int too)
{
    if (from == too)
    {
        int t = 0;
        stack_t *te = energy;
        while (te != NULL)
        {
            t += te->data;
            te = te->next;
        }
        total = push(total, t);
        energy = pop(energy);
        return 0;
    }
    List *temp = map->NodeArr[from];
    already = push(already, from);
    while (temp != NULL)
    {
        if (!scan(already, temp->number))
        {
            energy = push(energy, temp->weight);
            if (shortest_path(map, temp->number, too))
            {
                return 0;
            }
        }
        temp = temp->next;
    }
    already = pop(already);
    energy = pop(energy);
    return 0;
}

int main(void)
{
    Graph *mapping = NULL;
    int map_size, line, round, i, temp_from, temp_to, temp_weight, too, start;
    scanf("%d %d %d", &map_size, &line, &round);
    mapping = create_graph(map_size);
    for (i = 0; i < line; i++)
    {
        scanf("%d %d %d", &temp_from, &temp_to, &temp_weight);
        mapping = add(mapping, temp_from, temp_to, temp_weight);
    }

    for (i = 0; i < round; i++)
    {
        scanf("%d %d", &temp_from, &temp_to);
        shortest_path(mapping, temp_from, temp_to);
        int minn = 9999999;
        while (total != NULL)
        {
            if (top(total) < minn)
            {
                minn = top(total);
            }
            total = pop(total);
        }
        if (minn == 9999999)
        {
            printf("%d\n", -1);
        }
        else
        {
            printf("%d\n", minn);
        }
    }

    return 0;
}

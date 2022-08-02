#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;

struct node *append(struct node **List, int val)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = NULL;
    if (*List == NULL)
    {
        *List = temp;
    }
    else
    {
        struct node *ptr = *List;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
    return *List;
}

void get(struct node *List, int index)
{
    int i = 0;
    while (List != NULL)
    {
        if (index == i)
        {
            printf("%d\n", List->data);
            break;
        }
        i++;
        List = List->next;
    }
}

void show(struct node *List)
{
    while (List != NULL)
    {
        printf("%d ", List->data);
        List = List->next;
    }
    printf("\n");
}

struct node *reverse(struct node **List)
{
    struct node *previous = NULL;
    struct node *current = NULL;
    struct node *next = NULL;
    current = *List;
    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *List = previous;
    return *List;
}

struct node *cut(struct node **List, int froms, int too)
{
    struct node *from = NULL;
    struct node *tooo = NULL;
    int i = 0;
    while (*List != NULL)
    {
        if (froms == i)
        {
            from = *List;
        }
        if (too == i)
        {
            (*List)->next = NULL;
            tooo = *List;
        }
        i++;
        *List = (*List)->next;
    }
    return from;
}

int main(void)
{
    node_t *startNode;
    int n, i = 0;
    char command;
    int idx, val, from, too;
    startNode = NULL;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf(" %c", &command);
        switch (command)
        {
        case 'A':
            scanf("%d", &val);
            startNode = append(&startNode, val);
            break;
        case 'G':
            scanf("%d", &idx);
            get(startNode, idx);
            break;
        case 'S':
            show(startNode);
            break;
        case 'R':
            startNode = reverse(&startNode);
            break;
        case 'C':
            scanf("%d %d", &from, &too);
            startNode = cut(&startNode, from, too);
            break;
        default:
            break;
        }
    }
    return 0;
}
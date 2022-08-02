#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;

typedef node_t queue_t;

queue_t *enqueue(queue_t *q, int val)
{
    node_t *temp = (node_t *)malloc(sizeof(node_t));
    temp->data = val;
    temp->next = NULL;

    if (q == NULL)
    {
        temp->next = q;
        q = temp;
        return q;
    }
    else
    {
        node_t *ptr = q;
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
    node_t *temp = q;
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

void show(queue_t *q)
{
    if (q == NULL)
    {
        printf("Queue is empty.\n");
        return;
    }
    while (q != NULL)
    {
        printf("%d ", q->data);
        q = q->next;
    }
    printf("\n");
}

void empty(queue_t *q)
{
    if (q == NULL)
    {
        printf("Queue is empty.\n");
    }
    else
    {
        printf("Queue is not empty.\n");
    }
}

void size(queue_t *q)
{
    int i = 0;
    while (q != NULL)
    {
        i++;
        q = q->next;
    }
    printf("%d\n", i);
}

int main(void)
{
    queue_t *q = NULL;
    int n, i, command, value;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d", &value);
            q = enqueue(q, value);
            break;
        case 2:
            q = dequeue(q);
            break;
        case 3:
            show(q);
            break;
        case 4:
            empty(q);
            break;
        case 5:
            size(q);
            break;
        }
    }
    return 0;
}
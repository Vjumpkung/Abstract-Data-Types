#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;

typedef node_t stack_t;

stack_t *push(stack_t *s, int val)
{
    stack_t *temp = (stack_t *)malloc(sizeof(stack_t));
    temp->data = val;
    temp->next = NULL;

    temp->next = s;
    s = temp;
    return s;
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

void top(stack_t *s)
{
    if (s == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }
    printf("%d\n", (s)->data);
}

void empty(stack_t *s)
{
    if (s == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack is not empty.\n");
}

void size(stack_t *s)
{
    int i = 0;
    while (s != NULL)
    {
        i++;
        s = s->next;
    }
    printf("%d\n", i);
}

int main(void)
{
    stack_t *s = NULL;
    int n, i, command, value;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            scanf("%d", &value);
            s = push(s, value);
            break;

        case 2:
            top(s);
            break;

        case 3:
            s = pop(s);
            break;

        case 4:
            empty(s);
            break;

        case 5:
            size(s);
            break;

        default:
            break;
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack
{
    char data;
    struct stack *next;
} Stack;

void push(Stack **s, char val)
{
    Stack *temp = (Stack *)malloc(sizeof(Stack));
    temp->data = val;
    temp->next = NULL;

    temp->next = *s;
    *s = temp;
}

void pop(Stack **s)
{
    Stack *temp = *s;
    *s = (*s)->next;
    free(temp);
}

char top(Stack **s)
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

struct stack *reverse(struct stack **List)
{
    struct stack *previous = NULL;
    struct stack *current = NULL;
    struct stack *next = NULL;
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

int size(Stack *q)
{
    int i = 0;
    while (q != NULL)
    {
        i++;
        q = q->next;
    }
    return i;
}

void show(Stack *s)
{
    while (s != NULL)
    {
        printf("%c ", s->data);
        s = s->next;
    }
    printf("\n");
}

int main()
{
    char c;
    Stack *box = NULL, *revbox = NULL;
    while (1)
    {
        scanf(" %c", &c);
        if (c == 'x')
        {
            break;
        }
        else
        {
            push(&box, c);
        }
    }
    while (1)
    {
        scanf(" %c", &c);
        if (c == 'y')
        {
            break;
        }
        else
        {
            push(&revbox, c);
        }
    }
    revbox = reverse(&revbox);
    int size_box = size(box), size_revbox = size(revbox);
    char *s1 = (char *)malloc(sizeof(char) * (1 + size_box));
    char *s2 = (char *)malloc(sizeof(char) * (1 + size_revbox));
    int i = 0;
    for (i = 0; i < size_box; i++)
    {
        if (isEmpty(&box))
        {
            break;
        }
        s1[i] = top(&box);
        pop(&box);
    }
    s1[size_box] = '\0';
    for (i = 0; i < size_revbox; i++)
    {
        if (isEmpty(&revbox))
        {
            break;
        }
        s2[i] = top(&revbox);
        pop(&revbox);
    }
    s2[size_revbox] = '\0';

    if (strcmp(s1, s2) == 0)
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }
    return 0;
}

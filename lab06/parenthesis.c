#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char o[4] = "([{";
char c[4] = ")]}";

typedef struct stack
{
    char *sta;
    int size;
    int top;
} Stack;

void create(Stack *s, int Size)
{
    s->sta = (char *)malloc(sizeof(int) * Size);
    s->size = Size;
    s->top = -1;
}

void push(Stack *s, char val)
{
    s->top++;
    s->sta[s->top] = val;
}

void pop(Stack *s)
{
    s->sta[s->top] = ' ';
    s->top--;
}

int isEmpty(Stack *s)
{
    return 1 ? (s->top == -1) : 0;
}

char top(Stack *s)
{
    if (isEmpty(s))
    {
        return ' ';
    }
    return s->sta[s->top];
}

void print_stack(Stack *s)
{
    int i = 0;
    for (i = 0; i < s->top + 1; i++)
    {
        printf("%c ", s->sta[i]);
    }
    printf("\n");
}

int isOpen(char x)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        if (x == o[i])
        {
            return 1;
        }
    }
    return 0;
}

int isClose(char x)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        if (x == c[i])
        {
            return 1;
        }
    }
    return 0;
}

int isPattern(char open, char close)
{
    if (open == '[' && close == ']')
    {
        return 1;
    }
    else if (open == '{' && close == '}')
    {
        return 1;
    }
    else if (open == '(' && close == ')')
    {
        return 1;
    }
    return 0;
}

bool isValid(char *s)
{
    int i = 0;
    char open;
    Stack x = {NULL, 0, -1};
    create(&x, strlen(s));
    while (s[i] != '\0')
    {
        if (isOpen(s[i]))
        {
            push(&x, s[i]);
        }
        if (isClose(s[i]))
        {
            open = top(&x);
            if (!isPattern(open, s[i]))
            {
                return 0;
            }
            pop(&x);
        }
        i++;
    }
    if (!isEmpty(&x))
    {
        return 0;
    }
    return 1;
}

int main()
{
    int i;
    scanf("%d", &i);
    char *txt = (char *)malloc(sizeof(char) * (i + 1));
    scanf("%s", txt);
    printf("%d\n", isValid(txt));
    return 0;
}
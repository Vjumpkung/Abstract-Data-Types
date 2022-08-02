#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    float data;
    struct stack *next;
} Stack;

void push(Stack **s, float val)
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

float top(Stack **s)
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

int main()
{
    int i = 0, popcount = 0, idx = 0;
    float temp[2] = {0, 0};
    scanf("%d", &i);
    char *str = (char *)malloc(sizeof(char) * (i + 1));
    scanf("%s", str);
    Stack *box = NULL;
    int j = 0;
    for (j = 0; j < i; j++)
    {
        if (str[j] >= '0' && str[j] <= '9')
        {
            push(&box, str[j] - '0');
        }
        else if (str[j] == '+')
        {
            float sum = 0;
            while (idx < 2)
            {
                temp[1 - idx] = top(&box);
                pop(&box);
                idx++;
            }
            sum = temp[0] + temp[1];
            push(&box, sum);
            idx = 0;
        }
        else if (str[j] == '-')
        {
            float diff = 0;
            while (idx < 2)
            {
                temp[1 - idx] = top(&box);
                pop(&box);
                idx++;
            }
            diff = temp[0] - temp[1];
            push(&box, diff);
            idx = 0;
        }
        else if (str[j] == '*')
        {
            float prod = 0;
            while (idx < 2)
            {
                temp[1 - idx] = top(&box);
                pop(&box);
                idx++;
            }
            prod = temp[0] * temp[1];
            push(&box, prod);
            idx = 0;
        }
        else if (str[j] == '/')
        {
            float div = 0;
            while (idx < 2)
            {
                temp[1 - idx] = top(&box);
                pop(&box);
                idx++;
            }
            div = temp[0] / temp[1];
            push(&box, div);
            idx = 0;
        }
    }
    printf("%.2f\n", top(&box));
    return 0;
}
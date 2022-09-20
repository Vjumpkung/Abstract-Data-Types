#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXTSIZE 21

typedef struct item
{
    char *text;
    struct item *next;
} item_t;

typedef struct hash
{
    item_t **table;
    int size;
    int hash_key;
} hash_t;

unsigned int f(char *x, int hash_key, int idx)
{
    if (idx == 0)
    {
        return x[idx];
    }
    else
    {
        return (hash_key * f(x, hash_key, idx - 1)) + x[idx];
    }
}

unsigned int hash(char *x, int hash_key, int table_size, int charlen)
{
    return f(x, hash_key, charlen - 1) % table_size;
}

item_t *Insert_List(item_t *items, char *txt)
{
    item_t *node = (item_t *)malloc(sizeof(item_t));
    node->text = (char *)malloc(sizeof(char) * strlen(txt));
    strcpy(node->text, txt);
    node->next = NULL;
    if (items == NULL)
    {
        return node;
    }
    else
    {
        node->next = items;
        items = node;
        return items;
    }
}

void insert(hash_t *desk, char *text)
{
    unsigned int hashed = hash(text, desk->hash_key, desk->size, strlen(text));
    desk->table[hashed] = Insert_List(desk->table[hashed], text);
}

hash_t *init_hashtable(int m, int hash_key)
{
    hash_t *desk = (hash_t *)malloc(sizeof(hash_t *));
    desk->table = (item_t **)malloc(sizeof(item_t *) * m);
    desk->hash_key = hash_key;
    desk->size = m;
    int i;
    for (i = 0; i < m; i++)
    {
        desk->table[i] = NULL;
    }
    return desk;
}

int search(hash_t *desk, char *text)
{
    unsigned int hashed = hash(text, desk->hash_key, desk->size, strlen(text));
    item_t *temp = desk->table[hashed];
    int found = 0;
    while (temp != NULL)
    {
        if (strcmp(text, temp->text) == 0)
        {
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (found)
    {
        return hashed;
    }
    else
    {
        return -1;
    }
}

int main(void)
{
    hash_t *hashtable = NULL;
    char *text = NULL;
    int m, n, i, hash_key;
    int command;
    scanf("%d %d %d", &m, &n, &hash_key);
    hashtable = init_hashtable(m, hash_key);
    text = (char *)malloc(sizeof(char) * TEXTSIZE);

    for (i = 0; i < n; i++)
    {
        scanf("%d %s", &command, text);
        switch (command)
        {
        case 1:
            insert(hashtable, text);
            break;
        case 2:
            printf("%d\n", search(hashtable, text));
            break;
        }
    }
    return 0;
}
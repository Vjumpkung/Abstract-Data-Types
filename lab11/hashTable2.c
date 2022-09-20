#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXTSIZE 21

typedef char *item_t;

typedef struct hash
{
    item_t *table;
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

hash_t *init_hashtable(int m, int hash_key)
{
    hash_t *desk = (hash_t *)malloc(sizeof(hash_t *));
    desk->table = (item_t *)malloc(sizeof(item_t *) * m);
    desk->hash_key = hash_key;
    desk->size = m;
    int i;
    for (i = 0; i < m; i++)
    {
        desk->table[i] = NULL;
    }
    return desk;
}

int F(int i)
{
    return (i + i * i) / 2;
}

void insert(hash_t *desk, char *text)
{
    unsigned int hashed = hash(text, desk->hash_key, desk->size, strlen(text));
    if (desk->table[hashed] == NULL)
    {
        desk->table[hashed] = (char *)malloc(sizeof(char) * (strlen(text) + 1));
        strcpy(desk->table[hashed], text);
    }
    else
    {
        int i = 0;
        while (desk->table[(hashed + F(i)) % desk->size] != NULL)
        {
            i++;
        }
        desk->table[(hashed + F(i)) % desk->size] = (char *)malloc(sizeof(char) * (strlen(text) + 1));
        strcpy(desk->table[(hashed + F(i)) % desk->size], text);
    }
}

int search(hash_t *desk, char *text)
{
    unsigned int hashed = hash(text, desk->hash_key, desk->size, strlen(text));
    int found = 0;
    int temp = 0;
    int x;
    if (desk->table[hashed] != NULL && !strcmp(desk->table[hashed], text))
    {
        return hashed;
    }
    else
    {
        int i = 0;
        int summation = (desk->size - 1) * (desk->size) / 2;
        while (summation > temp)
        {
            temp += (hashed + F(i)) % desk->size;
            if (desk->table[(hashed + F(i)) % desk->size] != NULL)
            {
                if (strcmp(text, desk->table[(hashed + F(i)) % desk->size]) == 0)
                {
                    found = 1;
                    x = (hashed + F(i)) % desk->size;
                    break;
                }
            }
            i++;
        }
    }
    if (found)
    {
        return x;
    }
    return -1;
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
#include <stdio.h>
#include <stdlib.h>

typedef struct cell
{
    int data;
    int mem_addr;
} cell_t;

typedef struct hash
{
    cell_t *table;
    int cache_size;
} hash_t;

typedef hash_t cache_t;
typedef int memory_t;

memory_t *init_memory(int size)
{
    memory_t *memory = (memory_t *)malloc(sizeof(memory_t) * size);
    int i = 0;
    for (i = 0; i < size; i++)
    {
        memory[i] = rand();
    }
    return memory;
}

unsigned int cache_index(int mem_addr, int cache_size)
{
    return mem_addr % cache_size;
}

cache_t *init_cache(int cache_size)
{
    cache_t *ram = (cache_t *)malloc(sizeof(cache_t));
    ram->table = (cell_t *)malloc(sizeof(cell_t) * cache_size);
    ram->cache_size = cache_size;
    int i = 0;
    for (i = 0; i < cache_size; i++)
    {
        ram->table[i].data = -1;
        ram->table[i].mem_addr = -1;
    }
    return ram;
}

void get_data(int addr, memory_t *ram, cache_t *cache)
{
    int i = 0, j = 0;
    int cindex = cache_index(addr, cache->cache_size);
    if (ram[addr] == cache->table[cindex].data)
    {
        printf("Address %d is loaded\n", addr);
    }
    else
    {
        if (cache->table[cindex].data == -1 && cache->table[cindex].mem_addr == -1)
        {
            printf("Load from memory\n");
        }
        else
        {
            printf("Index: %d is used\n", cindex);
            printf("Load from memory\n");
        }
        cache->table[cindex].data = ram[addr];
        cache->table[cindex].mem_addr = addr;
    }
    printf("Data: %d\n", cache->table[cindex].data);
}

int main(void)
{
    memory_t *memory = NULL;
    cache_t *cache = NULL;
    int memory_size, cache_size;
    int i, n, addr;

    scanf("%d %d %d", &memory_size, &cache_size, &n);
    memory = init_memory(memory_size);
    cache = init_cache(cache_size);

    for (i = 0; i < n; i++)
    {
        printf("Load address: ");
        scanf("%d", &addr);
        get_data(addr, memory, cache);
    }
    return 0;
}

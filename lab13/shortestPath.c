#include <stdio.h>
#include <stdlib.h>
#define INF 0xfffffff

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

int shortest_path(Graph *map, int from, int too)
{
    int i, j;
    int dist[map->size], visited[map->size];
    for (i = 0; i < map->size; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[from] = 0;
    for (i = 0; i < map->size; i++)
    {
        int argmin = 0;
        int minn = INF;
        for (j = 0; j < map->size; j++)
        {
            if (!visited[j] && dist[j] < minn)
            {
                minn = dist[j];
                argmin = j;
            }
        }
        visited[argmin] = 1;
        List *temp = map->NodeArr[argmin]->next;
        while (temp != NULL)
        {
            if (dist[temp->number] > dist[argmin] + temp->weight)
            {
                dist[temp->number] = dist[argmin] + temp->weight;
            }
            temp = temp->next;
        }
    }
    return dist[too];
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
        mapping = add(mapping, temp_from - 1, temp_to - 1, temp_weight);
    }

    for (i = 0; i < round; i++)
    {
        scanf("%d %d", &temp_from, &temp_to);
        int minn = shortest_path(mapping, temp_from - 1, temp_to - 1);
        if (minn == INF)
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

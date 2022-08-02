#include <stdio.h>
/*
12
############
#   #      #
S # # #### #
### #    # #
#    ### # #
#### # # # G
#  # # # # #
## # # # # #
#        # #
###### ### #
#      #   #
############
*/

int start[2] = {0, 0}, end[2] = {0, 0}, s_found = 0, g_found = 0;

int traverseMaze(int start_y, int start_x, void *maze, int n)
{
    char(*p_maze)[n][n] = (char(*)[n][n])maze;
    (*p_maze)[start_y][start_x] = '.';

    if (start_y == end[0] && start_x == end[1])
    {
        return 1;
    }
    if (start_y + 1 < n && ((*p_maze)[start_y + 1][start_x] == ' ' || (*p_maze)[start_y + 1][start_x] == 'G'))
    {
        if (traverseMaze(start_y + 1, start_x, (*p_maze), n))
        {
            return 1;
        }
    }
    if (start_y - 1 >= 0 && ((*p_maze)[start_y - 1][start_x] == ' ' || (*p_maze)[start_y - 1][start_x] == 'G'))
    {
        if (traverseMaze(start_y - 1, start_x, (*p_maze), n))
        {
            return 1;
        }
    }
    if (start_x + 1 < n && ((*p_maze)[start_y][start_x + 1] == ' ' || (*p_maze)[start_y][start_x + 1] == 'G'))
    {
        if (traverseMaze(start_y, start_x + 1, (*p_maze), n))
        {
            return 1;
        }
    }
    if (start_x - 1 >= 0 && ((*p_maze)[start_y][start_x - 1] == ' ' || (*p_maze)[start_y][start_x - 1] == 'G'))
    {
        if (traverseMaze(start_y, start_x - 1, (*p_maze), n))
        {
            return 1;
        }
    }

    (*p_maze)[start_y][start_x] = ' ';

    return 0;
}

int main(void)
{
    int n, i, j;
    scanf("%d", &n);
    char maze[n][n], c;
    for (i = -1; i < n; i++)
    {
        j = 0;
        while (1)
        {
            c = getchar();
            if (c == '\n')
            {
                break;
            }
            else
            {
                maze[i][j] = c;
                j++;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (maze[i][j] == 'S' && !s_found)
            {
                start[0] = i;
                start[1] = j;
                s_found = 1;
            }
            if (maze[i][j] == 'G' && !g_found)
            {
                end[0] = i;
                end[1] = j;
                g_found = 1;
            }
        }
        if (s_found && g_found)
        {
            break;
        }
    }

    if (traverseMaze(start[0], start[1], maze, n))
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (i == start[0] && j == start[1])
                {
                    printf("S");
                }
                else if (i == end[0] && j == end[1])
                {
                    printf("G");
                }
                else
                {
                    printf("%c", maze[i][j]);
                }
            }
            putchar('\n');
        }
    }

    return 0;
}
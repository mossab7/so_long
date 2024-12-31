#include "so_long.h"

void free_map_resources(char **map, int size)
{
    if (!map)
        return;
    for (int i = 0; i < size; i++)
    {
        if (map[i])
            free(map[i]);
    }
    free(map);
}

int ft_realloc(char ***arr, char *str, int size)
{
    char **tmp;
    int i;

    tmp = malloc((size + 1) * sizeof(char*));
    if (!tmp)
        return (-1);
    
    for (i = 0; i < size - 1; i++)
    {
        if (!(tmp[i] = ft_strdup((*arr) ? (*arr)[i] : "")))
        {
            free_map_resources(tmp, i);
            return (-1);
        }
    }
    
    if (!(tmp[i] = ft_strdup(str)))
    {
        free_map_resources(tmp, i);
        return (-1);
    }
    tmp[size] = NULL; 
    if (*arr)
        free_map_resources(*arr, size - 1);
    
    *arr = tmp;
    return (0);
}

int read_map(char *map_path, t_game *game)
{
    int fd;
    char *tmp;

    if (!game || !map_path)
        return (-1);
    
    game->map.map = NULL;
    game->map.height = 0;

    if ((fd = open(map_path, O_RDONLY)) == -1)
    {
        ft_putendl_fd("Error: Cannot open map file", 2);
        return (-1);
    }

    while (1)
    {
        tmp = get_next_line(fd);
        if (!tmp)
            break;
        game->map.height++;
        if (ft_realloc(&game->map.map, tmp, game->map.height) == -1)
        {
            free(tmp);
            close(fd);
            return (-1);
        }
        free(tmp);
    }
    close(fd);
    game->map.width = ft_strlen(game->map.map[0]);
    return (game->map.height > 0 ? 0 : -1);
}


t_stack *create_stack(int capacity)
{
    t_stack *stack = malloc(sizeof(t_stack));
    stack->points = malloc(sizeof(t_point) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(t_stack *stack, t_point point)
{
    if (stack->top < stack->capacity - 1)
        stack->points[++stack->top] = point;
}

t_point pop(t_stack *stack)
{
    return stack->points[stack->top--];
}

int is_empty(t_stack *stack)
{
    return stack->top == -1;
}

char  **search_for_path(char **tab, t_point size, t_point begin,const char *obstacls)
{
    char **visited;
    t_stack *stack;
    
    stack = create_stack(size.x * size.y);
    visited = malloc(sizeof(char *) * size.y);
    for (int i = 0; i < size.y; i++)
        visited[i] = calloc(size.x, sizeof(char));
        
    push(stack, begin);

    while (!is_empty(stack))
    {
        t_point cur = pop(stack);
        
        if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x 
            || (ft_strchr(obstacls,tab[cur.y][cur.x]) != NULL) ||visited[cur.y][cur.x])
            continue;
            
        visited[cur.y][cur.x] = 1; 
        
        push(stack, (t_point){cur.x - 1, cur.y});
        push(stack, (t_point){cur.x + 1, cur.y});
        push(stack, (t_point){cur.x, cur.y - 1});
        push(stack, (t_point){cur.x, cur.y + 1});
    }

    free(stack->points);
    free(stack);
    return visited;
}


void get_player_and_exit_pos(t_game *game)
{
    for(int i = 0;i<game->map.height;i++)
    {
        for(int j = 0;j<game->map.width;j++)
        {
            if(game->map.map[i][j] == 'P')
            {
                game->player.x_pos = j;
                game->player.y_pos = i;
            }
            if(game->map.map[i][j] == 'E')
            {
                game->portal.x_pos = j;
                game->portal.y_pos = i;
            }
        }
    }
}


int check_path(t_game *game)
{
        char **visited;

        get_player_and_exit_pos(game);
        visited = search_for_path(game->map.map,(t_point){.x=game->map.width, .y=game->map.height},(t_point){.x=game->player.x_pos,.y=game->player.y_pos},"1X");
        if(visited[game->portal.y_pos][game->portal.x_pos] == 1)
            return 0;
        return -1;
}


int check_map_if_valid(t_game *game)
{
    if(check_path(game) == -1)
        return -1;
    return 0;
}
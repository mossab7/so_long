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

static char **allocate_new_array(int size)
{
    char **tmp = malloc((size + 1) * sizeof(char*));
    if (!tmp)
        return NULL;
    tmp[size] = NULL;
    return tmp;
}

static int copy_existing_elements(char **tmp, char **old_arr, int size)
{
    int i = 0;
    
    while (i < size - 1 && old_arr)
    {
        tmp[i] = ft_strdup(old_arr[i]);
        if (!tmp[i])
        {
            free_map_resources(tmp, i);
            return (-1);
        }
        i++;
    }
    return (0);
}

int ft_realloc(char ***arr, char *str, int size)
{
    char **tmp;
    
    if (!arr || !str || size <= 0)
        return (-1);

    tmp = allocate_new_array(size);
    if (!tmp)
        return (-1);
    
    if (copy_existing_elements(tmp, *arr, size) == -1)
        return (-1);
    
    tmp[size - 1] = ft_strdup(str);
    if (!tmp[size - 1])
    {
        free_map_resources(tmp, size - 1);
        return (-1);
    }

    if (*arr)
        free_map_resources(*arr, size - 1);
    
    *arr = tmp;
    return (0);
}

static int initialize_map(t_game *game, char *map_path)
{
    if (!game || !map_path)
    {
        ft_putendl_fd("Error: Invalid parameters", 2);
        return (-1);
    }
    
    game->map.map = NULL;
    game->map.height = 0;
    game->map.width = 0;
    
    return (0);
}

static int process_map_line(t_game *game, char *line)
{
    if (!line)
        return (0);

    game->map.height++;
    if (ft_realloc(&game->map.map, line, game->map.height) == -1)
        return (-1);

    if (game->map.width == 0)
        game->map.width = ft_strlen(line);
        
    return (0);
}

int read_map(char *map_path, t_game *game)
{
    int fd;
    char *line;

    if (initialize_map(game, map_path) == -1)
        return (-1);

    if ((fd = open(map_path, O_RDONLY)) == -1)
    {
        ft_putendl_fd("Error: Cannot open map file", 2);
        return (-1);
    }

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (process_map_line(game, line) == -1)
        {
            free(line);
            close(fd);
            return (-1);
        }
        free(line);
    }
    close(fd);
    
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

char **search_for_path(char **tab, t_point size, t_point begin, const char *obstacles)
{
    char **visited = NULL;
    t_stack *stack = NULL;
    int i = 0;
    
    if (!tab || !obstacles || size.x <= 0 || size.y <= 0)
        return NULL;
    
    if (!(stack = create_stack(size.x * size.y)))
        return NULL;
        
    visited = malloc(sizeof(char *) * size.y);
    if (!visited)
    {
        free(stack->points);
        free(stack);
        return NULL;
    }
    
    while (i < size.y)
    {
        if (!(visited[i] = calloc(size.x, sizeof(char))))
        {
            while (--i >= 0)
                free(visited[i]);
            free(visited);
            free(stack->points);
            free(stack);
            return NULL;
        }
        i++;
    }
    
    push(stack, begin);
    while (!is_empty(stack))
    {
        t_point cur = pop(stack);
        
        if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x 
            || ft_strchr(obstacles, tab[cur.y][cur.x]) || visited[cur.y][cur.x])
            continue;
            
        visited[cur.y][cur.x] = 1;
        
        t_point moves[] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        i = 0;
        while (i < 4)
        {
            push(stack, (t_point){cur.x + moves[i].x, cur.y + moves[i].y});
            i++;
        }
    }

    free(stack->points);
    free(stack);
    return visited;
}

static void get_player_and_exit_pos(t_game *game)
{
    int i = 0;
    int j;
    
    if (!game || !game->map.map)
        return;
        
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            if (game->map.map[i][j] == 'P')
            {
                game->player.x_pos = j;
                game->player.y_pos = i;
            }
            else if (game->map.map[i][j] == 'E')
            {
                game->portal.x_pos = j;
                game->portal.y_pos = i;
            }
            j++;
        }
        i++;
    }
}

int check_path(t_game *game)
{
    char **visited;
    int result;
    int i = 0;
    
    if (!game)
        return -1;
        
    get_player_and_exit_pos(game);
    
    visited = search_for_path(game->map.map,
                            (t_point){game->map.width, game->map.height},
                            (t_point){game->player.x_pos, game->player.y_pos},
                            "1X");
    
    if (!visited)
        return -1;
        
    result = visited[game->portal.y_pos][game->portal.x_pos] ? 0 : -1;
    
    while (i < game->map.height)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
    
    return result;
}

int check_map_if_valid(t_game *game)
{
    if (!game)
        return -1;
    return check_path(game);
}
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
    game->map.hight = 0;

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
        game->map.hight++;
        if (ft_realloc(&game->map.map, tmp, game->map.hight) == -1)
        {
            free(tmp);
            close(fd);
            return (-1);
        }
        free(tmp);
    }
    close(fd);
    return (game->map.hight > 0 ? 0 : -1);
}
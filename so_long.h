#ifndef SO_LONG_H
#define SO_LONG_H

#include "includes/libft/libft.h"
#include "includes/minilibx-linux/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>


typedef struct s_map
{
    char **map;
    int hight;
    int width;
} t_map;

typedef struct s_game
{
    t_map map;
    void *mlx;
    void *mlx_win;
}t_game;

void free_map_resources(char **map, int size);
int ft_realloc(char ***arr, char *str, int size);
int read_map(char *map_path, t_game *game);
int start_game(t_game *game);
#endif
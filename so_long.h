#ifndef SO_LONG_H
#define SO_LONG_H

#include "includes/libft/libft.h"
#include "includes/minilibx-linux/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define SCALE 32

typedef struct s_map
{
    char **map;
    int height;
    int width;
} t_map;

typedef enum e_key
{
    ESC = 65307,
    UPPER_KEY = 65362,  
    LEFT_KEY = 65361,
    DOWN_KEY = 65364,
    RIGHT_KEY = 65363
} t_key;               

typedef struct s_player
{
    void *player_image;
    int player_pos_x;
    int player_pos_y;
}t_player;

typedef struct s_vars
{
    void *image;
    void *image_addr;
    int bpp;
    int line_size;
    int endian;
    int height;
    int width;
    int x_pos;
    int y_pos;
    int x_start_pos;
    int y_start_pos;
}t_vars;

typedef struct s_game
{
    t_map map;
    void *mlx;
    void *win;
    void *image;
    void *image_addr;
    int bpp;
    int line_size;
    int endian;
    int height;
    int width;
    t_vars player;
    t_vars enemy;
    t_vars obstacl;
    t_vars floor;
    t_vars collectable;
}t_game;

void free_map_resources(char **map, int size);
int ft_realloc(char ***arr, char *str, int size);
int read_map(char *map_path, t_game *game);
int start_game(t_game *game);
#endif
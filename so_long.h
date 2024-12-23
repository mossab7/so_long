#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdio.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
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
}t_game;

#endif
#ifndef SO_LONG_H
#define SO_LONG_H

#include "includes/libft/libft.h"
#include "includes/minilibx-linux/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

#define MAX_MOVES 4
#define SCALE 32
#define NUM_ENEMIES 7

typedef struct s_move {
    int dx;
    int dy;
    float score;
} t_move;

typedef struct s_map
{
    char **map;
    int height;
    int width;
} t_map;


typedef enum e_key
{
    ESC = 65307,
    UP = 65362,  
    LEFT = 65361,
    DOWN = 65364,
    RIGHT = 65363
} t_key;

typedef struct s_point
{
    int x;
    int y;
} t_point;

typedef struct s_stack
{
    t_point *points;
    int     top;
    int     capacity;
} t_stack;

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
    int x_end_pos;
    int y_end_pos;
    int frame_x;
    int frame_y;
    t_key direction;
    t_key new_direction;
}t_vars;

typedef struct s_canvas
{
    void *image;
    void *image_addr;
    int bpp;
    int line_size;
    int endian;
    int height;
    int width;
}t_canvas;


typedef struct s_game
{
    t_map map;
    void *mlx;
    void *win;
    t_vars player;
    t_vars enemy[NUM_ENEMIES];
    t_vars obstacl;
    t_vars floor;
    t_vars portal;
    t_vars collectable;
    t_canvas canvas;
    int frame_counter;
    int frame_flag;
    int start_game_flag;
    int in_action;
    int enemies_counter;
}t_game;

void free_map_resources(char **map, int size);
int ft_realloc(char ***arr, char *str, int size);
int read_map(char *map_path, t_game *game);
int start_game(t_game *game);
void draw_player_and_enemeis_tile_to_image(int i_pos,int j_pos,t_vars *to_draw,t_game *game);
int handle_player_movement_input(int keycode, t_game *game);
void calculate_next_position(t_game *game);
void move_player_towards_target(t_game *game);
void update_enemy_sprite_direction(t_game *game);
void update_game_state(t_game *game);
int render_game_frame(t_game *game);
void animate_player_sprite(t_game *game);
void animate_enemy_sprite(t_game *game);
int update_sprite_animation_frame(t_game *game,t_vars *to_draw,int frames);
void render_character_movement(t_game *game,t_vars *to_draw,int in_action);
void update_all_characters_positions(t_game *game);
int render_next_game_frame(t_game *game);
int load_images(t_game *game);
int render_game_map(t_game *game);
int draw_sprite_to_canvas(t_game *game, t_vars to_draw);
int initialize_game_window(t_game *game);
void initialize_character_position(int i_pos,int j_pos,t_vars *to_draw,t_game *game);
void render_map_tile(int i_pos,int j_pos,t_vars *tile,t_game *game);
int check_map_if_valid(t_game *game);
#endif
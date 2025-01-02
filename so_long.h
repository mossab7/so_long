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

#define DEATH_FRAMES 9
#define DEATH_ANIMATION_SPEED 5
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
    int death_animation;
    int death_frame_counter;
    int death_animation_tick;
    int collectable_counter;
    int move_counter;
    
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
void clear_enemies_from_screen(t_game *game);
void game_over(t_game *game);
void cleanup_game(t_game *game);
void update_death_frame(t_game *game);
// Sprite and animation
void update_enemy_direction(t_vars *enemy, t_vars player);
int update_sprite_frame(t_vars *to_draw, int frames, int *frame_flag);
void draw_floor(t_game *game, int x, int y);
void draw_pixel(t_game *game, t_vars *to_draw, int x, int y, int src_x);

// Movement and collision
void render_movement(t_game *game, t_vars *to_draw, int in_action);
int is_overlapping(t_vars obj1, t_vars obj2, int overlap);
void update_enemy_position_step(t_vars *enemy);
int is_out_of_bounds(t_game *game, int x, int y);
int is_wall(t_game *game, int x, int y);
int is_enemy_collision(t_game *game, int enemy_idx, int x, int y);

// Game state
void setup_death_animation(t_game *game);
void handle_death_frame(t_game *game);
void cleanup_and_exit(t_game *game);
float get_aggression_factor(t_game *game, int enemy_idx);

// Enemy AI
float evaluate_direction_bonus(t_game *game, int enemy_idx, int new_x, int new_y);
float get_min_enemy_distance(t_game *game, int enemy_idx, int new_x, int new_y);
void apply_random_move(t_vars *enemy, t_move *moves, int valid_moves);
void apply_best_move(t_vars *enemy, t_move *moves, int valid_moves);
void update_enemy_position(t_game *game, int enemy_idx, t_move *moves, int valid_moves);
void clear_enemies(t_game *game);
void calculate_next_position(t_game *game);
int is_valid_move(t_game *game, int enemy_idx, int new_x, int new_y);
float evaluate_move(t_game *game, int enemy_idx, int new_x, int new_y);
float calculate_distance(int x1, int y1, int x2, int y2);
// Enemy movement calculation prototypes
void init_direction_arrays(int *dx, int *dy);
void calculate_possible_moves(t_game *game, t_vars *enemy, int enemy_idx, 
                            t_move *moves, int *valid_moves, const int *dx, const int *dy);
void process_enemy_moves(t_game *game, t_vars *enemy, int enemy_idx);
void calculate_enemy_next_position(t_game *game);
void	free_map_resources(char **map, int size);
void destroy_image(t_vars *img_var);
t_game *get_game_instance(void);
void check_collision(t_game *game);
void handle_death(t_game *game);
#endif
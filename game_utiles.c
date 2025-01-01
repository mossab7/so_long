#include "so_long.h"

void render_map_tile(int i_pos,int j_pos,t_vars *tile,t_game *game)
{
    tile->x_pos = j_pos * SCALE;
    tile->y_pos = i_pos * SCALE;
    draw_sprite_to_canvas(game, *tile);
}

void initialize_character_position(int i_pos,int j_pos,t_vars *to_draw,t_game *game)
{
    to_draw->x_start_pos = j_pos * SCALE;
    to_draw->y_start_pos = i_pos * SCALE;
    to_draw->x_pos = to_draw->x_start_pos;
    to_draw->y_pos = to_draw->y_start_pos;
    to_draw->x_end_pos = to_draw->x_pos;
    to_draw->y_end_pos = to_draw->y_pos;
    draw_sprite_to_canvas(game, *to_draw);
}


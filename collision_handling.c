#include "so_long.h"

void check_collision(t_game *game)
{
    int overlap = SCALE/2;
    int i = 0;
    while(i < game->enemies_counter)
    {
        if(is_overlapping(game->player, game->enemy[i], overlap))
        {
            game_over(game);
            draw_sprite_to_canvas(game, game->player);
            return;
        }
        i++;
    }
}

int is_overlapping(t_vars obj1, t_vars obj2, int overlap)
{
    return (obj1.x_pos + overlap >= obj2.x_pos && 
            obj1.x_pos <= obj2.x_pos + overlap &&
            obj1.y_pos + overlap >= obj2.y_pos && 
            obj1.y_pos <= obj2.y_pos + overlap);
}

int is_valid_move(t_game *game, int enemy_idx, int new_x, int new_y)
{
    if(is_out_of_bounds(game, new_x, new_y) || 
       is_wall(game, new_x, new_y) ||
       is_enemy_collision(game, enemy_idx, new_x, new_y))
        return 0;
    return 1;
}

int is_out_of_bounds(t_game *game, int x, int y)
{
    return (x < 0 || x >= game->map.width * SCALE || 
            y < 0 || y >= game->map.height * SCALE);
}

int is_wall(t_game *game, int x, int y)
{
    return (game->map.map[y / SCALE][x / SCALE] == '1');
}
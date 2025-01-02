#include "so_long.h"

int render_next_game_frame(t_game *game)
{

    if(game->frame_counter % 100 == 0)
    {
        animate_player_sprite(game);
        animate_enemy_sprite(game);
    }
    update_all_characters_positions(game);        
    return 0;
}

void draw_floor(t_game *game, int x, int y)
{
    game->floor.x_pos = x;
    game->floor.y_pos = y;
    draw_sprite_to_canvas(game, game->floor);
}

int draw_sprite_to_canvas(t_game *game, t_vars to_draw)
{
    int x;
    int y;

    y = 0;
    while (y < SCALE)
    {
        x = 0;
        while (x < SCALE)
        {
            draw_pixel(game, &to_draw, x, y, to_draw.frame_x + x);
            x++;
        }
        to_draw.frame_y++;
        y++;
    }
    return 0;
}

void draw_pixel(t_game *game, t_vars *to_draw, int x, int y, int src_x)
{
    char *src = to_draw->image_addr + 
                (to_draw->frame_y * to_draw->line_size + 
                 src_x * (to_draw->bpp / 8));
                 
    if(*(unsigned int *)src != 0xFF000000)
    {
        char *dst = game->canvas.image_addr + 
                    ((to_draw->y_pos + y) * game->canvas.line_size + 
                     (to_draw->x_pos + x) * (game->canvas.bpp / 8));
        *(unsigned int *)dst = *(unsigned int *)src;
    }
}

int render_game_frame(t_game *game)
{
    game->frame_counter++;
    if(game->frame_counter % 10 == 0)
        update_game_state(game);
    render_next_game_frame(game);
    handle_death(game);
    mlx_put_image_to_window(game->mlx, game->win, game->canvas.image, 0, 0);
    return 0;
}
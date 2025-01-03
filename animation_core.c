#include "so_long.h"

int update_sprite_animation_frame(t_game *game,t_vars *to_draw,int frames)
{
    if(game->start_game_flag == 0)
        return 0;
    if(to_draw->frame_x >= SCALE*frames || game->frame_flag == 1)
            to_draw->frame_x -= SCALE;
    else if(to_draw->frame_x < SCALE*frames)
            to_draw->frame_x += SCALE;
    if(to_draw->frame_x == SCALE*frames)
        game->frame_flag = 1;
    else if(to_draw->frame_x == 0)
        game->frame_flag = 0;
    return 0;
}



// void draw_collactable(t_game *game,t_vars to_draw)
// {
//     static int i = 0;
//     if(game->map.map[to_draw.y_pos / SCALE][to_draw.x_pos / SCALE] == 'C')
//     {
//         if(to_draw.x_start_pos > to_draw.x_end_pos)
//             game->collectable.x_pos = to_draw.x_start_pos - SCALE;
//         else  if(to_draw.x_start_pos < to_draw.x_end_pos)
//             game->collectable.x_pos = to_draw.x_start_pos + SCALE;
//         else if(to_draw.y_start_pos > to_draw.y_end_pos)
//             game->collectable.y_pos = to_draw.y_start_pos - SCALE;
//         else if(to_draw.y_start_pos < to_draw.y_end_pos)
//             game->collectable.y_pos = to_draw.y_start_pos + SCALE;
//         draw_sprite_to_canvas(game, game->collectable);
//         printf("%d\n",i++);
//     }

// }



void draw_collectable(t_game *game, int x, int y)
{
    game->collectable.x_pos = x;
    game->collectable.y_pos = y;
    draw_sprite_to_canvas(game, game->collectable);
}

void redraw_collectable(t_game *game)
{
    int i;
    int j;

    i = 0;
    while(i < game->map.height)
    {
        j = 0;
        while(j < game->map.width)
        {
            if(game->map.map[i][j] == 'C')
                draw_collectable(game,j * SCALE,i * SCALE);
            j++;
        }
        i++;
    }
}

void render_character_movement(t_game *game, t_vars *to_draw, int in_action, int is_enemy)
{
    if(in_action == 1)
    {
        draw_floor(game, to_draw->x_start_pos, to_draw->y_start_pos);
        to_draw->x_start_pos = to_draw->x_pos;
        to_draw->y_start_pos = to_draw->y_pos;
        draw_sprite_to_canvas(game, *to_draw);
        if(game->frame_counter % 100 == 0)
            redraw_collectable(game);
    }
    else
    {
        to_draw->x_pos = to_draw->x_start_pos;
        to_draw->y_pos = to_draw->y_start_pos;
    }
}



void update_all_characters_positions(t_game *game)
{
    int i;

    render_character_movement(game,&game->player,game->in_action,0);
    i = 0;
    while(i < game->enemies_counter)
        render_character_movement(game,&game->enemy[i++],game->start_game_flag,1);
}

void animate_player_sprite(t_game *game)
{
    if(game->player.frame_y == SCALE * 4)
    {
        game->frame_flag = 0;
        update_sprite_animation_frame(game,&game->player,9);
    }
    else
        update_sprite_animation_frame(game,&game->player,2);
}

void animate_enemy_sprite(t_game *game)
{
    int i;

    i = 0;
    while(i < game->enemies_counter)
        update_sprite_animation_frame(game,&game->enemy[i++],1);
}
#include "so_long.h"

void update_enemy_sprite_direction(t_game *game)
{
    int i = 0;
    while(i < game->enemies_counter)
    {
        if(game->enemy[i].x_pos > game->player.x_pos)
            game->enemy[i].frame_y = SCALE;
        else if(game->enemy[i].y_pos > game->player.y_pos)
            game->enemy[i].frame_y = SCALE*3;

        if(game->enemy[i].x_pos < game->player.x_pos)
            game->enemy[i].frame_y = 0;
        else if(game->enemy[i].y_pos < game->player.y_pos)
            game->enemy[i].frame_y = SCALE*2;
        i++;

    }
}

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

void render_character_movement(t_game *game,t_vars *to_draw,int in_action)
{
         if(in_action == 1)
        {
            game->floor.x_pos = to_draw->x_start_pos;
            game->floor.y_pos = to_draw->y_start_pos;
            draw_sprite_to_canvas(game, game->floor);
            to_draw->x_start_pos = to_draw->x_pos;
            to_draw->y_start_pos = to_draw->y_pos;
            draw_sprite_to_canvas(game, *to_draw);
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

    render_character_movement(game,&game->player,game->in_action);
    i = 0;
    while(i < game->enemies_counter)
        render_character_movement(game,&game->enemy[i++],game->start_game_flag);
}

void animate_player_sprite(t_game *game)
{
    update_sprite_animation_frame(game,&game->player,2);
}

void play_daying_aimation(t_game *game)
{
    int i = 0;
    while(i < game->enemies_counter)
    {
        //
        update_sprite_animation_frame(game,&game->enemy[i],2);
        i++;
    }
}

void game_over(t_game *game)
{
    play_daying_aimation(game);
    mlx_destroy_window(game->mlx, game->win);
    ft_putstr_fd("Game Over\n", 1);
    exit(0);
}


void check_player_enemy_collision(t_game *game)
{
    int i = 0;
    while (i < game->enemies_counter)
    {
        if (game->player.x_end_pos == game->enemy[i].x_pos && game->player.y_end_pos == game->enemy[i].y_pos)
        {
            game_over(game);
        }
        i++;
    }
}

void animate_enemy_sprite(t_game *game)
{
    int i;

    i = 0;
    while(i < game->enemies_counter)
        update_sprite_animation_frame(game,&game->enemy[i++],1);
}

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

void update_game_state(t_game *game)
{
    move_player_towards_target(game);
    update_enemy_sprite_direction(game);
    check_player_enemy_collision(game);
}

int render_game_frame(t_game *game)
{
    game->frame_counter++;
    if(game->frame_counter % 10 == 0)
        update_game_state(game);
    render_next_game_frame(game);
    mlx_put_image_to_window(game->mlx, game->win, game->canvas.image, 0, 0);
    return (0);
}
#include "so_long.h"

void init_direction_arrays(int *dx, int *dy)
{
    dx[0] = SCALE;
    dx[1] = -SCALE;
    dx[2] = 0;
    dx[3] = 0;
    dy[0] = 0;
    dy[1] = 0;
    dy[2] = SCALE;
    dy[3] = -SCALE;
}

void calculate_possible_moves(t_game *game, t_vars *enemy, int enemy_idx, 
                            t_move *moves, int *valid_moves, const int *dx, const int *dy)
{
    int m = 0;
    *valid_moves = 0;
    
    while(m < MAX_MOVES)
    {
        int new_x = enemy->x_pos + dx[m];
        int new_y = enemy->y_pos + dy[m];
        
        if(is_valid_move(game, enemy_idx, new_x, new_y))
        {
            moves[*valid_moves].dx = dx[m];
            moves[*valid_moves].dy = dy[m];
            moves[*valid_moves].score = evaluate_move(game, enemy_idx, new_x, new_y);
            (*valid_moves)++;
        }
        m++;
    }
}

void process_enemy_moves(t_game *game, t_vars *enemy, int enemy_idx)
{
    if(enemy->x_end_pos != enemy->x_pos || enemy->y_end_pos != enemy->y_pos)
        return;

    t_move moves[MAX_MOVES];
    int valid_moves = 0;
    int dx[MAX_MOVES];
    int dy[MAX_MOVES];
    
    init_direction_arrays(dx, dy);
    calculate_possible_moves(game, enemy, enemy_idx, moves, &valid_moves, dx, dy);
    update_enemy_position(game, enemy_idx, moves, valid_moves);
}

void calculate_enemy_next_position(t_game *game)
{
    if(!game || !game->start_game_flag)
        return;

    int i = 0;
    while(i < game->enemies_counter)
    {
        process_enemy_moves(game, &game->enemy[i], i);
        i++;
    }
}

void update_enemy_direction(t_vars *enemy, t_vars player)
{
    if(enemy->x_pos > player.x_pos)
        enemy->frame_y = SCALE;
    else if(enemy->y_pos > player.y_pos)
        enemy->frame_y = SCALE*3;
    else if(enemy->x_pos < player.x_pos)
        enemy->frame_y = 0;
    else if(enemy->y_pos < player.y_pos)
        enemy->frame_y = SCALE*2;
}
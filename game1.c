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

//start


// Helper function to calculate distance between two points
float calculate_distance(int x1, int y1, int x2, int y2) 
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Helper function to check if a move is valid
int is_valid_move(t_game *game, int enemy_idx, int new_x, int new_y) 
{
    // Check map boundaries
    if (new_x < 0 || new_x >= game->map.width * SCALE || 
        new_y < 0 || new_y >= game->map.height * SCALE)
        return 0;
    
    // Check wall collision
    if (game->map.map[new_y / SCALE][new_x / SCALE] == '1')
        return 0;
        
    // Check collision with other enemies
    for (int j = 0; j < game->enemies_counter; j++) 
    {
        if (j != enemy_idx && 
            game->enemy[j].x_pos == new_x && 
            game->enemy[j].y_pos == new_y)
            return 0;
    }
    
    return 1;
}

// Helper function to evaluate move based on multiple factors
float evaluate_move(t_game *game, int enemy_idx, int new_x, int new_y) 
{
    float score = 0.0f;
    
    // Distance to player (primary factor)
    float dist_to_player = calculate_distance(new_x, new_y, 
        game->player.x_pos, game->player.y_pos);
    score -= dist_to_player * 2.0f; // Higher weight for player distance
    
    // Distance to other enemies (secondary factor)
    float min_enemy_dist = INFINITY;
    for (int j = 0; j < game->enemies_counter; j++) 
    {
        if (j != enemy_idx) {
            float enemy_dist = calculate_distance(new_x, new_y,
                game->enemy[j].x_pos, game->enemy[j].y_pos);
            min_enemy_dist = fmin(min_enemy_dist, enemy_dist);
        }
    }
    score += min_enemy_dist * 0.5f; // Encourage some spacing between enemies
    
    // Bonus for moves that maintain current direction (reduces erratic movement)
    if ((new_x - game->enemy[enemy_idx].x_pos) == 
        (game->enemy[enemy_idx].x_pos - game->enemy[enemy_idx].x_start_pos) &&
        (new_y - game->enemy[enemy_idx].y_pos) == 
        (game->enemy[enemy_idx].y_pos - game->enemy[enemy_idx].y_start_pos))
        score += 10.0f;
    
    return score;
}

void calculate_enemy_next_position(t_game *game) 
{
    if (!game || !game->start_game_flag)
        return;

    // Possible moves: right, left, down, up
    const int dx[MAX_MOVES] = {SCALE, -SCALE, 0, 0};
    const int dy[MAX_MOVES] = {0, 0, SCALE, -SCALE};
    
    for (int i = 0; i < game->enemies_counter; i++) 
    {
        t_vars *enemy = &game->enemy[i];
        
        // Only calculate new position if enemy has reached its current destination
        if (enemy->x_end_pos != enemy->x_pos || enemy->y_end_pos != enemy->y_pos)
            continue;

        // Initialize possible moves array
        t_move moves[MAX_MOVES];
        int valid_moves = 0;

        // Calculate scores for all possible moves
        for (int m = 0; m < MAX_MOVES; m++) 
        {
            int new_x = enemy->x_pos + dx[m];
            int new_y = enemy->y_pos + dy[m];
            
            if (is_valid_move(game, i, new_x, new_y)) 
            {
                moves[valid_moves].dx = dx[m];
                moves[valid_moves].dy = dy[m];
                moves[valid_moves].score = evaluate_move(game, i, new_x, new_y);
                valid_moves++;
            }
        }

        // If there are valid moves available
        if (valid_moves > 0) {
            // Add randomness based on game state
            float aggression = calculate_distance(enemy->x_pos, enemy->y_pos,
                game->player.x_pos, game->player.y_pos) < SCALE * 5 ? 0.9f : 0.7f;
                
            if (rand() / (float)RAND_MAX > aggression) 
            {
                // Random move
                int move_idx = rand() % valid_moves;
                enemy->x_end_pos = enemy->x_pos + moves[move_idx].dx;
                enemy->y_end_pos = enemy->y_pos + moves[move_idx].dy;
            } else 
            {
                // Find best move
                int best_move = 0;
                for (int m = 1; m < valid_moves; m++) 
                {
                    if (moves[m].score > moves[best_move].score)
                        best_move = m;
                }
                enemy->x_end_pos = enemy->x_pos + moves[best_move].dx;
                enemy->y_end_pos = enemy->y_pos + moves[best_move].dy;
            }
        }
    }
}
//end

void move_enemy_towards_target(t_game *game)
{
    int i = 0;
    while(i < game->enemies_counter)
    {
        if(game->enemy[i].y_pos < game->enemy[i].y_end_pos)
            game->enemy[i].y_pos++;
        else if(game->enemy[i].y_pos > game->enemy[i].y_end_pos)
            game->enemy[i].y_pos--;
        else if(game->enemy[i].x_pos < game->enemy[i].x_end_pos)
            game->enemy[i].x_pos++;
        else if(game->enemy[i].x_pos > game->enemy[i].x_end_pos)
            game->enemy[i].x_pos--;
        i++;
    }
    calculate_enemy_next_position(game);
}

void update_game_state(t_game *game)
{
    move_player_towards_target(game);
    update_enemy_sprite_direction(game);
    move_enemy_towards_target(game);
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

int render_game_map(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            if (game->map.map[i][j] == '0')
                render_map_tile(i,j,&game->floor,game);
             if (game->map.map[i][j] == '1')
                render_map_tile(i,j,&game->obstacl,game);
            else if (game->map.map[i][j] == 'C')
                render_map_tile(i,j,&game->collectable,game);
            else if (game->map.map[i][j] == 'E')
                render_map_tile(i,j,&game->portal,game);
            else if (game->map.map[i][j] == 'P')
                 initialize_character_position(i,j,&game->player,game);
            else if(game->map.map[i][j] == 'X')
                 initialize_character_position(i,j,&game->enemy[game->enemies_counter++],game);
            j++;
        }
        i++;
    }
    return (0);
}



int draw_sprite_to_canvas(t_game *game, t_vars to_draw)
{
    int y = 0;
    int x;
    int src_x;
    char *src;
    char *dst;

    while (y < SCALE)
    {
        x = 0;
        src_x = to_draw.frame_x;
        while (x < SCALE)
        {
            src = to_draw.image_addr + (to_draw.frame_y * to_draw.line_size + src_x * (to_draw.bpp / 8));
            if (*(unsigned int *)src != 0xFF000000 && *(unsigned int *)src != 0x00000000 && 
                (*(unsigned int *)src & 0xFF000000) != 0xFF000000)  
            {
                dst = game->canvas.image_addr + ((to_draw.y_pos + y) * game->canvas.line_size + 
                    (to_draw.x_pos + x) * (game->canvas.bpp / 8));
                *(unsigned int *)dst = *(unsigned int *)src;
            }
            x++;
            src_x++;
        }
        y++;
        to_draw.frame_y++;
    }
    return (0);
}
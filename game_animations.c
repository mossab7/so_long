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

void update_enemy_sprite_direction(t_game *game)
{
    int i = 0;
    while(i < game->enemies_counter)
    {
        update_enemy_direction(&game->enemy[i], game->player);
        i++;
    }
}

int update_sprite_frame(t_vars *to_draw, int frames, int *frame_flag)
{
    if(to_draw->frame_x >= SCALE*frames || *frame_flag == 1)
        to_draw->frame_x -= SCALE;
    else if(to_draw->frame_x < SCALE*frames)
        to_draw->frame_x += SCALE;
    
    if(to_draw->frame_x == SCALE*frames)
        *frame_flag = 1;
    else if(to_draw->frame_x == 0)
        *frame_flag = 0;
    return 0;
}

void render_movement(t_game *game, t_vars *to_draw, int in_action)
{
    if(in_action)
    {
        draw_floor(game, to_draw->x_start_pos, to_draw->y_start_pos);
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

void draw_floor(t_game *game, int x, int y)
{
    game->floor.x_pos = x;
    game->floor.y_pos = y;
    draw_sprite_to_canvas(game, game->floor);
}

void update_positions(t_game *game)
{
    int i;

    render_movement(game, &game->player, game->in_action);
    i = 0;
    while(i < game->enemies_counter)
    {
        render_movement(game, &game->enemy[i], game->start_game_flag);
        i++;
    }
}

void animate_player(t_game *game)
{
    int frames;

    if (game->player.frame_y == SCALE * 4)
    {
        frames = 9;
        game->frame_flag = 0;
    }
    else
    {
        frames = 2;
    }
    update_sprite_frame(&game->player, frames, &game->frame_flag);
}

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

void game_over(t_game *game)
{
    clear_enemies(game);
    setup_death_animation(game);
    draw_sprite_to_canvas(game, game->player);
}

void setup_death_animation(t_game *game)
{
    game->death_animation = 1;
    game->death_frame_counter = 0;
    game->death_animation_tick = 0;
    game->player.frame_y = SCALE * 4;
    game->player.frame_x = 0;
}

void handle_death_frame(t_game *game)
{
    draw_floor(game, game->player.x_pos, game->player.y_pos);
    game->player.frame_x = (game->death_frame_counter % DEATH_FRAMES) * SCALE;
    game->death_frame_counter++;
    draw_sprite_to_canvas(game, game->player);
    usleep(100000);
}

void handle_death(t_game *game)
{
    if(!game->death_animation)
        return;
        
    game->death_animation_tick++;
    if(game->death_animation_tick >= DEATH_ANIMATION_SPEED)
    {
        game->death_animation_tick = 0;
        handle_death_frame(game);
        
        if(game->death_frame_counter >= DEATH_FRAMES)
            cleanup_and_exit(game);
    }
}

void cleanup_and_exit(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    exit(0);
}

void clear_enemies(t_game *game)
{
    int i = 0;
    while (i < game->enemies_counter)
    {
        draw_floor(game, game->enemy[i].x_pos, game->enemy[i].y_pos);
        i++;
    }
    game->enemies_counter = 0;
}

float calculate_distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
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

int is_enemy_collision(t_game *game, int enemy_idx, int x, int y)
{
    int j = 0;
    while(j < game->enemies_counter)
    {
        if(j != enemy_idx && 
           game->enemy[j].x_pos == x && 
           game->enemy[j].y_pos == y)
            return 1;
        j++;
    }
    return 0;
}

float evaluate_move(t_game *game, int enemy_idx, int new_x, int new_y)
{
    float score = -calculate_distance(new_x, new_y, 
                                    game->player.x_pos, 
                                    game->player.y_pos) * 2.0f;
    
    score += get_min_enemy_distance(game, enemy_idx, new_x, new_y) * 0.5f;
    score += evaluate_direction_bonus(game, enemy_idx, new_x, new_y);
    
    return score;
}

float get_min_enemy_distance(t_game *game, int enemy_idx, int new_x, int new_y)
{
    float min_dist = INFINITY;
    int j = 0;
    while(j < game->enemies_counter)
    {
        if(j != enemy_idx)
        {
            float dist = calculate_distance(new_x, new_y,
                                         game->enemy[j].x_pos, 
                                         game->enemy[j].y_pos);
            min_dist = fmin(min_dist, dist);
        }
        j++;
    }
    return min_dist;
}

float evaluate_direction_bonus(t_game *game, int enemy_idx, int new_x, int new_y)
{
    t_vars *enemy = &game->enemy[enemy_idx];
    if((new_x - enemy->x_pos) == (enemy->x_pos - enemy->x_start_pos) &&
       (new_y - enemy->y_pos) == (enemy->y_pos - enemy->y_start_pos))
        return 10.0f;
    return 0.0f;
}

void update_enemy_position(t_game *game, int enemy_idx, t_move *moves, int valid_moves)
{
    t_vars *enemy = &game->enemy[enemy_idx];
    if(valid_moves > 0)
    {
        float aggression = get_aggression_factor(game, enemy_idx);
        if(rand() / (float)RAND_MAX > aggression)
            apply_random_move(enemy, moves, valid_moves);
        else
            apply_best_move(enemy, moves, valid_moves);
    }
}

float get_aggression_factor(t_game *game, int enemy_idx)
{
    float dist = calculate_distance(game->enemy[enemy_idx].x_pos,
                                  game->enemy[enemy_idx].y_pos,
                                  game->player.x_pos,
                                  game->player.y_pos);
    if (dist < SCALE * 5)
        return 0.9f;
    else
        return 0.7f;
}

void apply_random_move(t_vars *enemy, t_move *moves, int valid_moves)
{
    int move_idx = rand() % valid_moves;
    enemy->x_end_pos = enemy->x_pos + moves[move_idx].dx;
    enemy->y_end_pos = enemy->y_pos + moves[move_idx].dy;
}

void apply_best_move(t_vars *enemy, t_move *moves, int valid_moves)
{
    int best_move = 0;
    int m = 1;
    while(m < valid_moves)
    {
        if(moves[m].score > moves[best_move].score)
            best_move = m;
        m++;
    }
    enemy->x_end_pos = enemy->x_pos + moves[best_move].dx;
    enemy->y_end_pos = enemy->y_pos + moves[best_move].dy;
}

void move_enemy_towards_target(t_game *game)
{
    int i = 0;
    while(i < game->enemies_counter)
    {
        update_enemy_position_step(&game->enemy[i]);
        i++;
    }
    calculate_enemy_next_position(game);
}

void update_enemy_position_step(t_vars *enemy)
{
    if(enemy->y_pos < enemy->y_end_pos)
        enemy->y_pos++;
    else if(enemy->y_pos > enemy->y_end_pos)
        enemy->y_pos--;
    else if(enemy->x_pos < enemy->x_end_pos)
        enemy->x_pos++;
    else if(enemy->x_pos > enemy->x_end_pos)
        enemy->x_pos--;
}

void update_game_state(t_game *game)
{
    move_player_towards_target(game);
    update_enemy_sprite_direction(game);
    move_enemy_towards_target(game);
    check_collision(game);
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
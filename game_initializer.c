#include "so_long.h"


//TODO : add enemys
int key_prss_call_back(int keycode, t_game *game)
{
    game->start_game_flag = 1;
    if(keycode == ESC)
    {
        mlx_destroy_display(game->mlx);
        exit(1);
    }
    
    if(keycode == UP || keycode == 'w' || keycode == 'W')
    {
        game->new_direction = UP;
        game->player.frame_y = SCALE * 2;
    }
    else if(keycode == LEFT || keycode == 'a'|| keycode == 'A')
    {
        game->new_direction = LEFT;
        game->player.frame_y = SCALE * 3;
    }
    else if(keycode == RIGHT|| keycode == 'd'|| keycode == 'D')
    {
        game->new_direction = RIGHT;
        game->player.frame_y = 0;
    }
    else if(keycode == DOWN || keycode == 's'|| keycode == 'S')
    {
        game->new_direction = DOWN;
        game->player.frame_y = SCALE;
    }
    return 0;
}

void update_deraction(t_game *game)
{
    game->in_action = 0;

    if(game->player.y_pos < game->player.y_end_pos)
    {
        game->player.y_pos++;
        game->in_action = 1;
    }
    else if(game->player.y_pos > game->player.y_end_pos)
    {
        game->player.y_pos--;
        game->in_action = 1;
    }
    else if(game->player.x_pos < game->player.x_end_pos)
    {
        game->player.x_pos++;
        game->in_action = 1;
    }
    else if(game->player.x_pos > game->player.x_end_pos)
    {
        game->player.x_pos--;
        game->in_action = 1;
    }

    if(game->player.y_end_pos == game->player.y_pos && game->player.x_end_pos == game->player.x_pos)
    {
        game->direction = game->new_direction;
        if(game->direction == UP && game->map.map[(game->player.y_pos - SCALE)/SCALE][game->player.x_pos/SCALE] != '1')
            game->player.y_end_pos = game->player.y_pos - SCALE;
        else if(game->direction == DOWN && game->map.map[(game->player.y_pos + SCALE)/SCALE][game->player.x_pos/SCALE] != '1')
            game->player.y_end_pos = game->player.y_pos + SCALE;
        else if(game->direction == LEFT && game->map.map[game->player.y_pos/SCALE][(game->player.x_pos - SCALE)/SCALE] != '1')
            game->player.x_end_pos = game->player.x_pos - SCALE;
        else if(game->direction == RIGHT && game->map.map[game->player.y_pos/SCALE][(game->player.x_pos + SCALE)/SCALE] != '1')
            game->player.x_end_pos = game->player.x_pos + SCALE;
    }
}


int put_next_frame(t_game *game)
{
    game->frame_counter++;
    if(game->frame_counter % 10 == 0)
    {
        update_deraction(game);
    }
    draw_next_frame(game);
    mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);

    return (0);
}

int draw_animation(t_game *game)
{
    if(game->start_game_flag == 0)
        return 0;
    if(game->player.frame_x >= SCALE*2 || game->frame_flag == 1)
            game->player.frame_x -= SCALE;
    else if(game->player.frame_x < SCALE*2)
            game->player.frame_x += SCALE;
    if(game->player.frame_x == SCALE*2)
        game->frame_flag = 1;
    else if(game->player.frame_x == 0)
        game->frame_flag = 0;
    return 0;
}

int draw_next_frame(t_game *game)
{
    if(game->in_action == 1)
    {
        if(game->frame_counter % 100 == 0)
            draw_animation(game);
        game->floor.x_pos = game->player.x_start_pos;
        game->floor.y_pos = game->player.y_start_pos;
        draw_to_image(game, game->floor);
        game->player.x_start_pos = game->player.x_pos;
        game->player.y_start_pos = game->player.y_pos;
        draw_to_image(game, game->player);
    }
    else
    {
        game->player.x_pos = game->player.x_start_pos;
        game->player.y_pos = game->player.y_start_pos;
    }
    return 0;
}

int load_images(t_game *game)
{
    if (!(game->obstacl.image = mlx_xpm_file_to_image(game->mlx, "sprites/Other/Walls/wall.xpm",
        &game->obstacl.width, &game->obstacl.height)))
        return (-1);
    if (!(game->obstacl.image_addr = mlx_get_data_addr(game->obstacl.image,
        &game->obstacl.bpp, &game->obstacl.line_size, &game->obstacl.endian)))
        return (-1);
    if (!(game->floor.image = mlx_xpm_file_to_image(game->mlx, "sprites/Other/Walls/black.xpm",
        &game->floor.width, &game->floor.height)))
        return (-1);
    if (!(game->floor.image_addr = mlx_get_data_addr(game->floor.image,
        &game->floor.bpp, &game->floor.line_size, &game->floor.endian)))
        return (-1);
    if (!(game->collectable.image = mlx_xpm_file_to_image(game->mlx, "sprites/Other/Pacdots/pacdot_food.xpm",
        &game->collectable.width, &game->collectable.height)))
        return (-1);
    if (!(game->collectable.image_addr = mlx_get_data_addr(game->collectable.image,
        &game->collectable.bpp, &game->collectable.line_size, &game->collectable.endian)))
        return (-1);
    if (!(game->player.image = mlx_xpm_file_to_image(game->mlx, "pac_frames.xpm",
        &game->player.width, &game->player.height)))
        return (-1);
    if (!(game->player.image_addr = mlx_get_data_addr(game->player.image,
        &game->player.bpp, &game->player.line_size, &game->player.endian)))
        return (-1);
        
    return (0);
}

int draw_map_to_image(t_game *game)
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
            {
                game->floor.x_pos = j * SCALE;
                game->floor.y_pos = i * SCALE;
                draw_to_image(game, game->floor);
            }
             if (game->map.map[i][j] == '1')
            {
                game->obstacl.x_pos = j * SCALE;
                game->obstacl.y_pos = i * SCALE;
                draw_to_image(game, game->obstacl);
            }
            else if (game->map.map[i][j] == 'C')
            {
                game->collectable.x_pos = j * SCALE;
                game->collectable.y_pos = i * SCALE;
                draw_to_image(game, game->collectable);
            }
            else if (game->map.map[i][j] == 'P')
            {
                game->player.x_start_pos = j * SCALE;
                game->player.y_start_pos = i * SCALE;
                game->player.x_pos = game->player.x_start_pos;
                game->player.y_pos = game->player.y_start_pos;
                game->player.x_end_pos = game->player.x_pos;
                game->player.y_end_pos = game->player.y_pos;
                draw_to_image(game, game->player);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int draw_to_image(t_game *game, t_vars to_draw)
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
            if (*(unsigned int *)src != 0xFF000000)
            {
                dst = game->image_addr + ((to_draw.y_pos + y) * game->line_size + 
                    (to_draw.x_pos + x) * (game->bpp / 8));
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

int start_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (-1);
        
    game->win = mlx_new_window(game->mlx, (game->map.width - 1) * SCALE,
        (game->map.height + 3) * SCALE, "so_long");
    if (!game->win)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        return (-1);
    }
    
    game->image = mlx_new_image(game->mlx, game->map.width * SCALE,
        game->map.height * SCALE);
    if (!game->image)
    {
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        return (-1);
    }
    
    game->image_addr = mlx_get_data_addr(game->image, &game->bpp,
        &game->line_size, &game->endian);
    if (!game->image_addr)
    {
        mlx_destroy_image(game->mlx, game->image);
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        return (-1);
    }
    
    if (load_images(game) == -1)
        return (-1);
    if (draw_map_to_image(game) == -1)
        return (-1);
        
    mlx_loop_hook(game->mlx, put_next_frame, game);
    mlx_hook(game->win,2,1L<<0, key_prss_call_back, game);
    mlx_loop(game->mlx);
    return (0);
}


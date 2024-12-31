#include "so_long.h"

int load_images(t_game *game)
{
    char *image_path[] = {
        "sprites/Other/Walls/wall.xpm",
        "sprites/Other/Walls/black.xpm",
        "sprites/Other/Pacdots/pacdot_food.xpm",
        "pac_frames.xpm",
        "sprites/Other/Portal/portal.xpm",
        "sprites/Ghosts/R/red_ghost_frames.xpm",
        "sprites/Ghosts/Y/red_yellow_frames.xpm",
        "sprites/Ghosts/P/red_yellow_frames.xpm",
        "sprites/Ghosts/O/red_yellow_frames.xpm",
        "sprites/Ghosts/K/red_yellow_frames.xpm",
        "sprites/Ghosts/G/red_yellow_frames.xpm",
        "sprites/Ghosts/B/red_yellow_frames.xpm"
    };

    t_vars *images[] = {
        &game->obstacl,
        &game->floor,
        &game->collectable,
        &game->player,
        &game->portal,
        &game->enemy[0],
        &game->enemy[1],
        &game->enemy[2],
        &game->enemy[3],
        &game->enemy[4],
        &game->enemy[5],
        &game->enemy[6],
    };

    int i = 0;
    while (i < sizeof(images)/sizeof(t_vars *))
    {
        images[i]->image = mlx_xpm_file_to_image(game->mlx, image_path[i], &images[i]->width, &images[i]->height);
        if (!images[i]->image)
            return (-1);  

        images[i]->image_addr = mlx_get_data_addr(images[i]->image, &images[i]->bpp, &images[i]->line_size, &images[i]->endian);
        if (!images[i]->image_addr)
            return (-1); 
        i++; 
    }

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
            if (*(unsigned int *)src != 0xFF000000)
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

int initialize_game_window(t_game *game)
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
    
    game->canvas.image = mlx_new_image(game->mlx, game->map.width * SCALE,
        game->map.height * SCALE);
    if (!game->canvas.image)
    {
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        return (-1);
    }
    
    game->canvas.image_addr = mlx_get_data_addr(game->canvas.image, &game->canvas.bpp,
        &game->canvas.line_size, &game->canvas.endian);
    if (!game->canvas.image_addr)
    {
        mlx_destroy_image(game->mlx, game->canvas.image);
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        return (-1);
    }
    
    if (load_images(game) == -1)
        return (-1);
    if (render_game_map(game) == -1)
        return (-1);
        
    mlx_loop_hook(game->mlx, render_game_frame, game);
    mlx_hook(game->win,2,1L<<0, handle_player_movement_input, game);
    mlx_loop(game->mlx);
    return (0);
}


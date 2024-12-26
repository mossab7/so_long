#include "so_long.h"

//TO DO : implement a key hook
//keep in mind you don't have to keep floor location you can just skip by the scale and do the inamation, for the wall it's the same thing
//check the inamation downloaded
//keep track of inamation by a static variable?
//add map check
//spritese:https://github.com/madebypixel02/so_long/tree/main/sprites
//push you have one week


int put_next_frame(t_game *to_draw)
{
    mlx_put_image_to_window(to_draw->mlx, to_draw->win, to_draw->image, 0, 0);
    return (0);
}

int load_images(t_game *game)
{
    if (!(game->obstacl.image = mlx_xpm_file_to_image(game->mlx, "/home/mbouhia/game/sprites/Other/Walls/wall.xpm",
        &game->obstacl.width, &game->obstacl.height)))
        return (-1);
    if (!(game->obstacl.image_addr = mlx_get_data_addr(game->obstacl.image,
        &game->obstacl.bpp, &game->obstacl.line_size, &game->obstacl.endian)))
        return (-1);
    if (!(game->floor.image = mlx_xpm_file_to_image(game->mlx, "/home/mbouhia/game/sprites/Other/Walls/wall.xpm",
        &game->floor.width, &game->floor.height)))
        return (-1);
    if (!(game->floor.image_addr = mlx_get_data_addr(game->floor.image,
        &game->floor.bpp, &game->floor.line_size, &game->floor.endian)))
        return (-1);
    if (!(game->collectable.image = mlx_xpm_file_to_image(game->mlx, "/home/mbouhia/game/sprites/Other/Pacdots/pacdot_food.xpm",
        &game->collectable.width, &game->collectable.height)))
        return (-1);
    if (!(game->collectable.image_addr = mlx_get_data_addr(game->collectable.image,
        &game->collectable.bpp, &game->collectable.line_size, &game->collectable.endian)))
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
            else if (game->map.map[i][j] == '1')
            {
                game->obstacl.x_pos = j * SCALE;
                game->obstacl.y_pos = i * SCALE;
                draw_to_image(game, game->obstacl);
            }
            else if (game->map.map[i][j] == 'C')
            {
                game->floor.x_pos = j * SCALE;
                game->floor.y_pos = i * SCALE;
                game->collectable.x_pos = j * SCALE;
                game->collectable.y_pos = i * SCALE;
                draw_to_image(game, game->floor);
                draw_to_image(game, game->collectable);
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
    char *src;
    char *dst;

    while (y < SCALE)
    {
        x = 0;
        while (x < SCALE)
        {
            src = to_draw.image_addr + (y * to_draw.line_size + x * (to_draw.bpp / 8));
            if (*(unsigned int *)src != 0xFF000000)
            {
                dst = game->image_addr + ((to_draw.y_pos + y) * game->line_size + 
                    (to_draw.x_pos + x) * (game->bpp / 8));
                *(unsigned int *)dst = *(unsigned int *)src;
            }
            x++;
        }
        y++;
    }
    return (0);
}

int start_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (-1);
        
    game->win = mlx_new_window(game->mlx, (game->map.width - 1) * SCALE,
        game->map.height * SCALE, "so_long");
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
    mlx_loop(game->mlx);
    return (0);
}


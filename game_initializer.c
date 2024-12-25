#include "so_long.h"

int put_next_frame(t_game *to_draw)
{
    mlx_put_image_to_window(to_draw->mlx, to_draw->win, to_draw->image, 0, 0);
    return (0);
}

int load_images(t_game *game)
{
    if (!(game->obstacl.image = mlx_xpm_file_to_image(game->mlx, "obstacl.xpm",
        &game->obstacl.width, &game->obstacl.height)))
        return (-1);
    if (!(game->obstacl.image_addr = mlx_get_data_addr(game->obstacl.image,
        &game->obstacl.bpp, &game->obstacl.line_size, &game->obstacl.endian)))
        return (-1);
        
    if (!(game->floor.image = mlx_xpm_file_to_image(game->mlx, "floor.xpm",
        &game->floor.width, &game->floor.height)))
        return (-1);
    if (!(game->floor.image_addr = mlx_get_data_addr(game->floor.image,
        &game->floor.bpp, &game->floor.line_size, &game->floor.endian)))
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
            j++;
        }
        i++;
    }
    return (0);
}

int draw_to_image(t_game *game, t_vars to_draw)
{
    int y;
    int x;
    char *src;
    char *dst;
    
    y = 0;
    while (y < SCALE)
    {
        x = 0;
        while (x < SCALE)
        {
            src = to_draw.image_addr + (y * to_draw.line_size + x * (to_draw.bpp / 8));
            dst = game->image_addr + 
                  ((to_draw.y_pos + y) * game->line_size + 
                   (to_draw.x_pos + x) * (game->bpp / 8));
            *(unsigned int *)dst = *(unsigned int *)src;
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
        
    game->win = mlx_new_window(game->mlx, game->map.width * SCALE,
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


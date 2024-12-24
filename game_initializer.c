#include "so_long.h"

int lead_images(t_game *game)
{
    return 0;
}

int start_game(t_game *game)
{
    game->mlx = mlx_init();
    game->mlx_win = mlx_new_window(game->mlx, game->map.width*64, game->map.hight*64, "Hello world!");
	if(lead_images(game) == -1)
        return (-1);
    mlx_loop(game->mlx);
}
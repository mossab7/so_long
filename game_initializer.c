#include "so_long.h"

int start_game(t_game *game)
{
    game->mlx = mlx_init();
    game->mlx_win = mlx_new_window(game->mlx, 1920, 1080, "Hello world!");
	mlx_loop(game->mlx);
}
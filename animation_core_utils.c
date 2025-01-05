#include "so_long.h"

void	draw_collectable(t_game *game, int x, int y)
{
	game->collectable.x_pos = x;
	game->collectable.y_pos = y;
	draw_sprite_to_canvas(game, game->collectable);
}

void	redraw_collectable(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	if (game->map.map[game->player.y_end_pos / SCALE][game->player.x_end_pos
		/ SCALE] == 'C')
	{
		game->collectable_counter--;
		game->map.map[game->player.y_end_pos / SCALE][game->player.x_end_pos
			/ SCALE] = '0';
	}
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] == 'C')
				draw_collectable(game, j * SCALE, i * SCALE);
			j++;
		}
		i++;
	}
}

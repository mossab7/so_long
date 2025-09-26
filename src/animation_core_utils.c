/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_core_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:46:36 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:29 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_collectable(t_game *game, int x, int y)
{
	game->collectable.x_pos = x;
	game->collectable.y_pos = y;
	draw_sprite_to_canvas(game, game->collectable);
}

void	collect_item_at_position(t_game *game)
{
	int	player_map_x;
	int	player_map_y;

	player_map_x = game->player.x_end_pos / SCALE;
	player_map_y = game->player.y_end_pos / SCALE;
	
	if (game->map.map[player_map_y][player_map_x] == 'C')
	{
		game->collectable_counter--;
		game->map.map[player_map_y][player_map_x] = '0';
		draw_floor(game, player_map_x * SCALE, player_map_y * SCALE);
	}
}

void	redraw_all_collectables(t_game *game)
{
	int	i;
	int	j;

	i = 0;
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

void	redraw_collectable(t_game *game)
{
	redraw_all_collectables(game);
}

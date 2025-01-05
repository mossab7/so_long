/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:12 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/04 15:55:12 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_map_tile(int i_pos, int j_pos, t_vars *tile, t_game *game)
{
	tile->x_pos = j_pos * SCALE;
	tile->y_pos = i_pos * SCALE;
	draw_sprite_to_canvas(game, *tile);
}

void	initialize_character_position(int i_pos, int j_pos, t_vars *to_draw,
		t_game *game)
{
	to_draw->x_start_pos = j_pos * SCALE;
	to_draw->y_start_pos = i_pos * SCALE;
	to_draw->x_pos = to_draw->x_start_pos;
	to_draw->y_pos = to_draw->y_start_pos;
	to_draw->x_end_pos = to_draw->x_pos;
	to_draw->y_end_pos = to_draw->y_pos;
	draw_sprite_to_canvas(game, *to_draw);
}

void	check_tile(t_game *game, int i, int j)
{
	if (game->map.map[i][j] == '0')
		render_map_tile(i, j, &game->floor, game);
	if (game->map.map[i][j] == '1')
		render_map_tile(i, j, &game->obstacl, game);
	else if (game->map.map[i][j] == 'C')
		render_map_tile(i, j, &game->collectable, game);
	else if (game->map.map[i][j] == 'E')
		render_map_tile(i, j, &game->portal, game);
	else if (game->map.map[i][j] == 'P')
		initialize_character_position(i, j, &game->player, game);
	else if (game->map.map[i][j] == 'X')
		initialize_character_position(i, j,
			&game->enemy[game->enemies_counter++], game);
}

int	render_game_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			check_tile(game, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

void	destroy_image(void *img_var)
{
	t_vars *to_destroy;
	t_game *game;

	to_destroy = (t_vars *)img_var;
	game = get_game_instance();
	mlx_destroy_image(game->mlx, to_destroy->image);
}
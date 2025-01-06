/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_animations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:12 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:32 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_enemy_sprite_direction(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemies_counter)
	{
		update_enemy_direction(&game->enemy[i], game->player);
		i++;
	}
}

int	update_sprite_frame(t_vars *to_draw, int frames, int *frame_flag)
{
	if (to_draw->frame_x >= SCALE * frames || *frame_flag == 1)
		to_draw->frame_x -= SCALE;
	else if (to_draw->frame_x < SCALE * frames)
		to_draw->frame_x += SCALE;
	if (to_draw->frame_x == SCALE * frames)
		*frame_flag = 1;
	else if (to_draw->frame_x == 0)
		*frame_flag = 0;
	return (0);
}

void	clear_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemies_counter)
	{
		draw_floor(game, game->enemy[i].x_pos, game->enemy[i].y_pos);
		i++;
	}
	game->enemies_counter = 0;
}

float	calculate_distance(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int	is_enemy_collision(t_game *game, int enemy_idx, int x, int y)
{
	int	j;

	j = 0;
	while (j < game->enemies_counter)
	{
		if (j != enemy_idx && game->enemy[j].x_pos == x
			&& game->enemy[j].y_pos == y)
			return (1);
		j++;
	}
	return (0);
}

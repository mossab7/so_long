/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:11 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/04 15:55:11 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	update_sprite_animation_frame(t_game *game, t_vars *to_draw, int frames)
{
	if (game->start_game_flag == 0)
		return (0);
	if (to_draw->frame_x >= SCALE * frames || game->frame_flag == 1)
		to_draw->frame_x -= SCALE;
	else if (to_draw->frame_x < SCALE * frames)
		to_draw->frame_x += SCALE;
	if (to_draw->frame_x == SCALE * frames)
		game->frame_flag = 1;
	else if (to_draw->frame_x == 0)
		game->frame_flag = 0;
	return (0);
}

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

void	render_character_movement(t_game *game, t_vars *to_draw, int in_action)
{
	if (in_action == 1)
	{
		draw_floor(game, to_draw->x_start_pos, to_draw->y_start_pos);
		to_draw->x_start_pos = to_draw->x_pos;
		to_draw->y_start_pos = to_draw->y_pos;
		draw_sprite_to_canvas(game, *to_draw);
		if (game->frame_counter % 200 == 0)
			redraw_collectable(game);
	}
	else
	{
		to_draw->x_pos = to_draw->x_start_pos;
		to_draw->y_pos = to_draw->y_start_pos;
	}
}

void	update_all_characters_positions(t_game *game)
{
	int	i;

	render_character_movement(game, &game->player, game->in_action);
	i = 0;
	while (i < game->enemies_counter)
		render_character_movement(game, &game->enemy[i++],
			game->start_game_flag);
}

void	animate_player_sprite(t_game *game)
{
	if (game->player.frame_y == SCALE * 4)
	{
		game->frame_flag = 0;
		update_sprite_animation_frame(game, &game->player, 9);
	}
	else
		update_sprite_animation_frame(game, &game->player, 2);
}

void	animate_enemy_sprite(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemies_counter)
		update_sprite_animation_frame(game, &game->enemy[i++], 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_movements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:12 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:33 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_player_direction(int keycode, t_game *game)
{
	if (keycode == UP || keycode == 'w' || keycode == 'W')
	{
		game->player.new_direction = UP;
		game->player.frame_y = SCALE * 2;
	}
	else if (keycode == LEFT || keycode == 'a' || keycode == 'A')
	{
		game->player.new_direction = LEFT;
		game->player.frame_y = SCALE * 3;
	}
	else if (keycode == RIGHT || keycode == 'd' || keycode == 'D')
	{
		game->player.new_direction = RIGHT;
		game->player.frame_y = 0;
	}
	else if (keycode == DOWN || keycode == 's' || keycode == 'S')
	{
		game->player.new_direction = DOWN;
		game->player.frame_y = SCALE;
	}
}

int	handle_player_movement_input(int keycode, t_game *game)
{
	static int	first_move = 1;

	if (first_move)
	{
		game->start_game_flag = 1;
		game->player.frame_x = 0;
		first_move = 0;
	}
	if (keycode == ESC)
	{
		cleanup_and_exit(game);
	}
	update_player_direction(keycode, game);
	return (0);
}

void	calculate_next_position(t_game *game)
{
	if (game->player.y_end_pos == game->player.y_pos
		&& game->player.x_end_pos == game->player.x_pos)
	{
		game->player.direction = game->player.new_direction;
		if (game->player.direction == UP && game->map.map[(game->player.y_pos
					- SCALE) / SCALE][game->player.x_pos / SCALE] != '1')
			game->player.y_end_pos = game->player.y_pos - SCALE;
		else if (game->player.direction == DOWN
			&& game->map.map[(game->player.y_pos + SCALE)
				/ SCALE][game->player.x_pos / SCALE] != '1')
			game->player.y_end_pos = game->player.y_pos + SCALE;
		else if (game->player.direction == LEFT
			&& game->map.map[game->player.y_pos / SCALE][(game->player.x_pos
				- SCALE) / SCALE] != '1')
			game->player.x_end_pos = game->player.x_pos - SCALE;
		else if (game->player.direction == RIGHT
			&& game->map.map[game->player.y_pos / SCALE][(game->player.x_pos
				+ SCALE) / SCALE] != '1')
			game->player.x_end_pos = game->player.x_pos + SCALE;
		if (game->in_action == 1)
		{
			update_move_counter(game);
		}
	}
}

void	update_player_position_status(t_game *game)
{
	if (game->player.x_pos == game->player.x_end_pos
		&& game->player.y_pos == game->player.y_end_pos
		&& game->start_game_flag == 1)
	{
		calculate_next_position(game);
	}
}

void	move_player_towards_target(t_game *game)
{
	game->in_action = 0;
	if (game->player.y_pos < game->player.y_end_pos)
	{
		game->player.y_pos++;
		game->in_action = 1;
	}
	else if (game->player.y_pos > game->player.y_end_pos)
	{
		game->player.y_pos--;
		game->in_action = 1;
	}
	else if (game->player.x_pos < game->player.x_end_pos)
	{
		game->player.x_pos++;
		game->in_action = 1;
	}
	else if (game->player.x_pos > game->player.x_end_pos)
	{
		game->player.x_pos--;
		game->in_action = 1;
	}
	update_player_position_status(game);
}

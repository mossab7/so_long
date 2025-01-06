/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:12 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:31 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_direction_arrays(int *dx, int *dy)
{
	dx[0] = SCALE;
	dx[1] = -SCALE;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = SCALE;
	dy[3] = -SCALE;
}

void	calculate_possible_moves(t_game *game, t_vars *enemy, t_move *moves,
		t_move_vars *move_vars)
{
	int	m;
	int	new_x;
	int	new_y;

	m = 0;
	move_vars->valid_moves = 0;
	while (m < MAX_MOVES)
	{
		new_x = enemy->x_pos + move_vars->dx[m];
		new_y = enemy->y_pos + move_vars->dy[m];
		if (is_valid_move(game, move_vars->enemy_idx, new_x, new_y))
		{
			moves[move_vars->valid_moves].dx = move_vars->dx[m];
			moves[move_vars->valid_moves].dy = move_vars->dy[m];
			moves[move_vars->valid_moves].score = evaluate_move(game,
					move_vars->enemy_idx, new_x, new_y);
			(move_vars->valid_moves)++;
		}
		m++;
	}
}

void	process_enemy_moves(t_game *game, t_vars *enemy, int enemy_idx)
{
	t_move		moves[MAX_MOVES];
	t_move_vars	move_vars;

	if (enemy->x_end_pos != enemy->x_pos || enemy->y_end_pos != enemy->y_pos)
		return ;
	move_vars.valid_moves = 0;
	move_vars.enemy_idx = enemy_idx;
	init_direction_arrays(move_vars.dx, move_vars.dy);
	calculate_possible_moves(game, enemy, moves, &move_vars);
	update_enemy_position(game, enemy_idx, moves, move_vars.valid_moves);
}

void	calculate_enemy_next_position(t_game *game)
{
	int	i;

	if (!game || !game->start_game_flag)
		return ;
	i = 0;
	while (i < game->enemies_counter)
	{
		process_enemy_moves(game, &game->enemy[i], i);
		i++;
	}
}

void	update_enemy_direction(t_vars *enemy, t_vars player)
{
	if (enemy->x_pos > player.x_pos)
		enemy->frame_y = SCALE;
	else if (enemy->y_pos > player.y_pos)
		enemy->frame_y = SCALE * 3;
	else if (enemy->x_pos < player.x_pos)
		enemy->frame_y = 0;
	else if (enemy->y_pos < player.y_pos)
		enemy->frame_y = SCALE * 2;
}

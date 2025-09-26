/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:12 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:33 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_enemy_towards_target(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemies_counter)
	{
		update_enemy_position_step(&game->enemy[i]);
		i++;
	}
	calculate_enemy_next_position(game);
}

void	update_game_state(t_game *game)
{
	move_player_towards_target(game);
	update_enemy_sprite_direction(game);
	move_enemy_towards_target(game);
	draw_sprite_to_canvas(game, game->portal);
	draw_sprite_to_canvas(game, game->player);
	check_collision(game);
}

void	update_enemy_position_step(t_vars *enemy)
{
	if (enemy->y_pos < enemy->y_end_pos)
		enemy->y_pos++;
	else if (enemy->y_pos > enemy->y_end_pos)
		enemy->y_pos--;
	else if (enemy->x_pos < enemy->x_end_pos)
		enemy->x_pos++;
	else if (enemy->x_pos > enemy->x_end_pos)
		enemy->x_pos--;
}

void	apply_best_move(t_vars *enemy, t_move *moves, int valid_moves)
{
	int	best_move;
	int	m;

	best_move = 0;
	m = 1;
	while (m < valid_moves)
	{
		if (moves[m].score > moves[best_move].score)
			best_move = m;
		m++;
	}
	enemy->x_end_pos = enemy->x_pos + moves[best_move].dx;
	enemy->y_end_pos = enemy->y_pos + moves[best_move].dy;
}

void	apply_random_move(t_vars *enemy, t_move *moves, int valid_moves)
{
	int	move_idx;

	move_idx = rand() % valid_moves;
	enemy->x_end_pos = enemy->x_pos + moves[move_idx].dx;
	enemy->y_end_pos = enemy->y_pos + moves[move_idx].dy;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:11 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:31 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

float	evaluate_move(t_game *game, int enemy_idx, int new_x, int new_y)
{
	float	score;

	score = -calculate_distance(new_x, new_y, game->player.x_pos,
			game->player.y_pos) * 2.0f;
	score += get_min_enemy_distance(game, enemy_idx, new_x, new_y) * 0.5f;
	score += evaluate_direction_bonus(game, enemy_idx, new_x, new_y);
	return (score);
}

float	get_min_enemy_distance(t_game *game, int enemy_idx, int new_x,
		int new_y)
{
	float	min_dist;
	int		j;
	float	dist;

	min_dist = INFINITY;
	j = 0;
	while (j < game->enemies_counter)
	{
		if (j != enemy_idx)
		{
			dist = calculate_distance(new_x, new_y, game->enemy[j].x_pos,
					game->enemy[j].y_pos);
			min_dist = fmin(min_dist, dist);
		}
		j++;
	}
	return (min_dist);
}

float	evaluate_direction_bonus(t_game *game, int enemy_idx, int new_x,
		int new_y)
{
	t_vars	*enemy;

	enemy = &game->enemy[enemy_idx];
	if ((new_x - enemy->x_pos) == (enemy->x_pos - enemy->x_start_pos) && (new_y
			- enemy->y_pos) == (enemy->y_pos - enemy->y_start_pos))
		return (10.0f);
	return (0.0f);
}

void	update_enemy_position(t_game *game, int enemy_idx, t_move *moves,
		int valid_moves)
{
	t_vars	*enemy;
	float	aggression;

	enemy = &game->enemy[enemy_idx];
	if (valid_moves > 0)
	{
		aggression = get_aggression_factor(game, enemy_idx);
		if (rand() / (float)RAND_MAX > aggression)
			apply_random_move(enemy, moves, valid_moves);
		else
			apply_best_move(enemy, moves, valid_moves);
	}
}

float	get_aggression_factor(t_game *game, int enemy_idx)
{
	float	dist;

	dist = calculate_distance(game->enemy[enemy_idx].x_pos,
			game->enemy[enemy_idx].y_pos, game->player.x_pos,
			game->player.y_pos);
	if (dist < SCALE * 5)
		return (0.9f);
	else
		return (0.7f);
}

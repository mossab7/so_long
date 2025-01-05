/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:47:26 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:32 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_player_and_exit_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	if (!game || !game->map.map)
		return ;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] == 'P')
			{
				game->player.x_pos = j;
				game->player.y_pos = i;
			}
			else if (game->map.map[i][j] == 'C')
			{
				game->collectable_counter++;
			}
			j++;
		}
		i++;
	}
}

int	check_if_visited(t_game *game, char **visited)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] == 'E' || game->map.map[i][j] == 'C')
			{
				if (!visited[i][j])
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_duplicate(t_game *game)
{
	int (exit_counter), (player_counter), (enemies_counter), (i), (j);
	i = 0;
	exit_counter = 0;
	player_counter = 0;
	enemies_counter = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] == 'P')
				player_counter++;
			else if (game->map.map[i][j] == 'E')
				exit_counter++;
			else if (game->map.map[i][j] == 'X')
				enemies_counter++;
			j++;
		}
		i++;
	}
	if (exit_counter != 1 || player_counter != 1 || enemies_counter > 6)
		return (-1);
	return (0);
}

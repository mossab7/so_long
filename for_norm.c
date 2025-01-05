/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:47:26 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 18:47:27 by mbouhia          ###   ########.fr       */
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
	int i;
	int j;

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

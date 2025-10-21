/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:12 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:36 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	*get_game_instance(void)
{
	static t_game	game;

	return (&game);
}

int	main(int ac, char **av)
{
	t_game	*game;
	char	*map_path;

	game = get_game_instance();
	if (ac != 2)
		map_path = GOOGLE_MAP;
	else
		map_path = av[1];
	if (read_map(map_path, game) == -1)
	{
		ft_putendl_fd("Error: Failed to read map", 2);
		return (1);
	}
	if (check_map_if_valid(game) == -1)
	{
		ft_putendl_fd("Error: Map is NOT valid", 2);
		return (1);
	}
	if (initialize_game_window(game) == -1)
	{
		ft_putendl_fd("Error: Failed to launch the game", 2);
		free_map_resources(game->map.map, game->map.height);
		return (1);
	}
	return (0);
}

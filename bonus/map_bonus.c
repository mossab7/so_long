/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:12 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:34 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	process_map_line(t_game *game, char *line)
{
	int	width;

	if (!line)
		return (0);
	game->map.height++;
	if (ft_realloc(&game->map.map, line, game->map.height) == -1)
		return (-1);
	if (game->map.width == 0)
	{
		game->map.width = ft_strlen(line);
		if (game->map.map[game->map.height - 1][game->map.width - 2] != '\n')
			game->map.width--;
	}
	else
	{
		width = ft_strlen(line);
		if (game->map.map[game->map.height - 1][width - 2] != '\n')
			width--;
		if (game->map.width != width)
			return (-1);
	}
	return (0);
}

int	read_map(char *map_path, t_game *game)
{
	int		fd;
	char	*line;

	fd = initialize_map(game, map_path);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (process_map_line(game, line) == -1)
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
	}
	close(fd);
	if (game->map.height > 0)
		return (0);
	return (-1);
}

int	check_components(t_game *game)
{
	int	i;
	int	j;

	if (check_duplicate(game) == -1)
		return (-1);
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (!ft_strchr("10CXEP\n", game->map.map[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_boundaries(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < game->map.width)
	{
		if (!ft_strchr("1", game->map.map[0][j++]))
			return (-1);
	}
	i = 0;
	while (i < game->map.height - 1)
	{
		if (game->map.map[i][0] != '1' || game->map.map[i++][game->map.width
			- 1] != '1')
			return (-1);
	}
	j = 0;
	while (j < game->map.width)
	{
		if (!ft_strchr("1", game->map.map[game->map.height - 1][j++]))
			return (-1);
	}
	return (0);
}

int	check_map_if_valid(t_game *game)
{
	if (!game)
		return (-1);
	if (check_components(game) == -1)
		return (-1);
	if (check_boundaries(game) == -1)
		return (-1);
	if (check_path(game) == -1)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:46:09 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:35 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map_resources(char **map, int size)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < size)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

char	**allocate_new_array(int size)
{
	char	**tmp;

	tmp = malloc((size + 1) * sizeof(char *));
	if (!tmp)
		return (NULL);
	tmp[size] = NULL;
	return (tmp);
}

int	copy_existing_elements(char **tmp, char **old_arr, int size)
{
	int	i;

	i = 0;
	while (i < size - 1 && old_arr)
	{
		tmp[i] = ft_strdup(old_arr[i]);
		if (!tmp[i])
		{
			free_map_resources(tmp, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_realloc(char ***arr, char *str, int size)
{
	char	**tmp;

	if (!arr || !str || size <= 0)
		return (-1);
	tmp = allocate_new_array(size);
	if (!tmp)
		return (-1);
	if (copy_existing_elements(tmp, *arr, size) == -1)
		return (-1);
	tmp[size - 1] = ft_strdup(str);
	if (!tmp[size - 1])
	{
		free_map_resources(tmp, size - 1);
		return (-1);
	}
	if (*arr)
		free_map_resources(*arr, size - 1);
	*arr = tmp;
	return (0);
}

int	initialize_map(t_game *game, char *map_path)
{
	int	fd;

	if (!game || !map_path)
	{
		ft_putendl_fd("Error: Invalid parameters", 2);
		return (-1);
	}
	if (ft_strncmp(map_path + (ft_strlen(map_path) - 4), ".ber", 4) != 0)
		return (-1);
	game->map.map = NULL;
	game->map.height = 0;
	game->map.width = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error: Cannot open map file", 2);
		return (-1);
	}
	return (fd);
}

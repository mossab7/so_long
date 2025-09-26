/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:47:04 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:29 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_search(char ***visited, t_stack **stack, t_point size)
{
	int	i;
	int	j;

	*visited = malloc(sizeof(char *) * size.y);
	if (!*visited)
		return (0);
	i = 0;
	while (i < size.y)
	{
		(*visited)[i] = malloc(sizeof(char) * size.x);
		if (!(*visited)[i])
		{
			while (--i >= 0)
				free((*visited)[i]);
			free(*visited);
			return (0);
		}
		j = 0;
		while (j < size.x)
			(*visited)[i][j++] = 0;
		i++;
	}
	*stack = create_stack(size.x * size.y);
	return (*stack != NULL);
}

int	is_valid_pos(t_point pos, t_point size, char **tab, char **visited)
{
	if (pos.x < 0 || pos.x >= size.x || pos.y < 0 || pos.y >= size.y)
		return (0);
	if (visited[pos.y][pos.x])
		return (0);
	if (ft_strchr("1X", tab[pos.y][pos.x]))
		return (0);
	return (1);
}

void	set_moves(t_point moves[4])
{
	moves[0] = (t_point){0, -1};
	moves[1] = (t_point){1, 0};
	moves[2] = (t_point){0, 1};
	moves[3] = (t_point){-1, 0};
}

char	**search_for_path(char **tab, t_point size, t_point begin)
{
	char	**visited;
	t_stack	*stack;
	int		i;
	t_point	cur;
	t_point	moves[4];

	if (!init_search(&visited, &stack, size))
		return (NULL);
	push(stack, begin);
	while (!is_empty(stack))
	{
		cur = pop(stack);
		if (!is_valid_pos(cur, size, tab, visited))
			continue ;
		visited[cur.y][cur.x] = 1;
		set_moves(moves);
		i = 0;
		while (i < 4)
		{
			push(stack, (t_point){cur.x + moves[i].x, cur.y + moves[i].y});
			i++;
		}
	}
	free_stack(stack);
	return (visited);
}

int	check_path(t_game *game)
{
	char	**visited;
	int		result;
	int		i;

	i = 0;
	if (!game)
		return (-1);
	get_player_and_exit_pos(game);
	visited = search_for_path(game->map.map, (t_point){game->map.width,
			game->map.height}, (t_point){game->player.x_pos,
			game->player.y_pos});
	if (!visited)
		return (-1);
	result = check_if_visited(game, visited);
	while (i < game->map.height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
	return (result);
}

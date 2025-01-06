/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_counter_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:40:21 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/06 21:40:22 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	init_counter_image(t_game *game)
{
	game->counter.image = mlx_new_image(game->mlx, SCALE, SCALE);
	if (!game->counter.image)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_image(game->mlx, game->canvas.image);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (-1);
	}
	game->counter.image_addr = mlx_get_data_addr(game->counter.image,
			&game->counter.bpp, &game->counter.line_size,
			&game->counter.endian);
	if (!game->counter.image_addr)
	{
		mlx_destroy_image(game->mlx, game->counter.image);
		mlx_destroy_image(game->mlx, game->canvas.image);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (-1);
	}
	register_memory_allocation(get_memory_tracker(),
		create_memory_record(&game->counter, destroy_image));
	return (0);
}

void	update_move_counter(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->counter.image,
		((game->map.width * SCALE) / 2), ((game->map.height) * SCALE));
	mlx_string_put(game->mlx, game->win, ((game->map.width * SCALE) / 2),
		((game->map.height + 1) * SCALE), 0x00FFFFFF,
		ft_itoa(game->move_counter));
	game->move_counter++;
}

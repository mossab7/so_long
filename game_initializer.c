/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:12 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/04 15:55:12 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_mlx_and_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (-1);
	game->win = mlx_new_window(game->mlx, (game->map.width) * SCALE,
			(game->map.height + 2) * SCALE, "so_long");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (-1);
	}
	return (0);
}

int	init_canvas(t_game *game)
{
	game->canvas.image = mlx_new_image(game->mlx, game->map.width * SCALE,
			(game->map.height + 2) * SCALE);
	if (!game->canvas.image)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (-1);
	}
	game->canvas.image_addr = mlx_get_data_addr(game->canvas.image,
			&game->canvas.bpp, &game->canvas.line_size, &game->canvas.endian);
	if (!game->canvas.image_addr)
	{
		mlx_destroy_image(game->mlx, game->canvas.image);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (-1);
	}
	return (0);
}

int	cleanup_and_exit_wrapper(void *ptr)
{
	t_game	*game;

	game = (t_game *)ptr;
	cleanup_and_exit(game);
	return (0);
}

void	setup_game_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx, render_game_frame, game);
	mlx_hook(game->win, 2, 1L << 0, handle_player_movement_input, game);
	mlx_hook(game->win, 33, 0, cleanup_and_exit_wrapper, game);
}
int	initialize_game_window(t_game *game)
{
	if (init_mlx_and_window(game) == -1)
		return (-1);
	if (init_canvas(game) == -1)
		return (-1);
	if (load_images(game) == -1)
		return (-1);
	if (render_game_map(game) == -1)
		return (-1);
	setup_game_hooks(game);
	mlx_loop(game->mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:11 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:30 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_over(t_game *game)
{
	clear_enemies(game);
	setup_death_animation(game);
	draw_sprite_to_canvas(game, game->player);
}

void	setup_death_animation(t_game *game)
{
	game->death_animation = 1;
	game->death_frame_counter = 0;
	game->death_animation_tick = 0;
	game->player.frame_y = SCALE * 4;
	game->player.frame_x = 0;
}

void	handle_death_frame(t_game *game)
{
	draw_floor(game, game->player.x_pos, game->player.y_pos);
	game->player.frame_x = (game->death_frame_counter % DEATH_FRAMES) * SCALE;
	game->death_frame_counter++;
	draw_sprite_to_canvas(game, game->player);
	usleep(100000);
}

void	handle_death(t_game *game)
{
	if (!game->death_animation)
		return ;
	game->death_animation_tick++;
	if (game->death_animation_tick >= DEATH_ANIMATION_SPEED)
	{
		game->death_animation_tick = 0;
		handle_death_frame(game);
		printf("Death frame: %d\n", game->death_frame_counter);
		if (game->death_frame_counter >= DEATH_FRAMES)
			cleanup_and_exit(game);
	}
}

void	cleanup_and_exit(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->canvas.image);
	cleanup_memory_tracker(get_memory_tracker());
	free_map_resources(game->map.map, game->map.height);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

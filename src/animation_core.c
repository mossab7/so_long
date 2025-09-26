/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:55:11 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:28 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	update_sprite_animation_frame(t_game *game, t_vars *to_draw, int frames)
{
	if (game->start_game_flag == 0)
		return (0);
	if (to_draw->frame_x >= SCALE * frames || game->frame_flag == 1)
		to_draw->frame_x -= SCALE;
	else if (to_draw->frame_x < SCALE * frames)
		to_draw->frame_x += SCALE;
	if (to_draw->frame_x == SCALE * frames)
		game->frame_flag = 1;
	else if (to_draw->frame_x == 0)
		game->frame_flag = 0;
	return (0);
}

void	check_enemy_collectable_collision(t_game *game, t_vars *enemy)
{
	int	old_map_x;
	int	old_map_y;
	int	current_map_x;
	int	current_map_y;

	old_map_x = enemy->x_start_pos / SCALE;
	old_map_y = enemy->y_start_pos / SCALE;
	current_map_x = enemy->x_pos / SCALE;
	current_map_y = enemy->y_pos / SCALE;

	if (game->map.map[old_map_y][old_map_x] == 'C')
	{
		draw_collectable(game, old_map_x * SCALE, old_map_y * SCALE);
	}
	if (game->map.map[current_map_y][current_map_x] == 'C')
	{
		draw_collectable(game, current_map_x * SCALE, current_map_y * SCALE);
	}
}

void	render_character_movement(t_game *game, t_vars *to_draw, int in_action, int is_player)
{
	if (in_action == 1)
	{
		draw_floor(game, to_draw->x_start_pos, to_draw->y_start_pos);
		if (!is_player)
			check_enemy_collectable_collision(game, to_draw);
		to_draw->x_start_pos = to_draw->x_pos;
		to_draw->y_start_pos = to_draw->y_pos;
		draw_sprite_to_canvas(game, *to_draw);
		if (!is_player)
		{
			int curr_x = to_draw->x_pos / SCALE;
			int curr_y = to_draw->y_pos / SCALE;
			if (game->map.map[curr_y][curr_x] == 'C')
				draw_collectable(game, curr_x * SCALE, curr_y * SCALE);
		}
		if (is_player)
			collect_item_at_position(game);
	}
	else
	{
		to_draw->x_pos = to_draw->x_start_pos;
		to_draw->y_pos = to_draw->y_start_pos;
	}
}

void	update_all_characters_positions(t_game *game)
{
	int	i;

	render_character_movement(game, &game->player, game->in_action, 1);
	i = 0;
	while (i < game->enemies_counter)
		render_character_movement(game, &game->enemy[i++],
			game->start_game_flag, 0);
}

void	animate_player_sprite(t_game *game)
{
	if (game->player.frame_y == SCALE * 4)
	{
		game->frame_flag = 0;
		update_sprite_animation_frame(game, &game->player, 9);
	}
	else
		update_sprite_animation_frame(game, &game->player, 2);
}

void	animate_enemy_sprite(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemies_counter)
		update_sprite_animation_frame(game, &game->enemy[i++], 1);
}

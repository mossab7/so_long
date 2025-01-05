#include "so_long.h"

void	init_image_paths(char **image_path)
{
	image_path[0] = "sprites/Other/Walls/wall.xpm";
	image_path[1] = "sprites/Other/Walls/black.xpm";
	image_path[2] = "sprites/Other/Pacdots/pacdot_food.xpm";
	image_path[3] = "sprites/Pac-Man/pac_frames.xpm";
	image_path[4] = "sprites/Other/Portal/portal.xpm";
	image_path[5] = "sprites/Ghosts/R/red_ghost_frames.xpm";
	image_path[6] = "sprites/Ghosts/Y/red_yellow_frames.xpm";
	image_path[7] = "sprites/Ghosts/P/red_yellow_frames.xpm";
	image_path[8] = "sprites/Ghosts/O/red_yellow_frames.xpm";
	image_path[9] = "sprites/Ghosts/K/red_yellow_frames.xpm";
	image_path[10] = "sprites/Ghosts/G/red_yellow_frames.xpm";
	image_path[11] = "sprites/Ghosts/B/red_yellow_frames.xpm";
}

void	init_image_vars(t_game *game, t_vars **images)
{
	images[0] = &game->obstacl;
	images[1] = &game->floor;
	images[2] = &game->collectable;
	images[3] = &game->player;
	images[4] = &game->portal;
	images[5] = &game->enemy[0];
	images[6] = &game->enemy[1];
	images[7] = &game->enemy[2];
	images[8] = &game->enemy[3];
	images[9] = &game->enemy[4];
	images[10] = &game->enemy[5];
	images[11] = &game->enemy[6];
}

int	load_single_image(t_game *game, t_vars *img_var, char *path)
{
	img_var->image = mlx_xpm_file_to_image(game->mlx, path, &img_var->width,
			&img_var->height);
	if (!img_var->image)
		return (-1);
	img_var->image_addr = mlx_get_data_addr(img_var->image, &img_var->bpp,
			&img_var->line_size, &img_var->endian);
	if (!img_var->image_addr)
		return (-1);
	register_memory_allocation(get_memory_tracker(),
		create_memory_record(img_var, destroy_image));
	return (0);
}

int	load_images(t_game *game)
{
	char	*image_path[12];
	t_vars	*images[12];
	int		i;

	init_image_paths(image_path);
	init_image_vars(game, images);
	i = 0;
	while (i < 12)
	{
		if (load_single_image(game, images[i], image_path[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
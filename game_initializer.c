#include "so_long.h"

static void init_image_paths(char **image_path)
{
    image_path[0] = "sprites/Other/Walls/wall.xpm";
    image_path[1] = "sprites/Other/Walls/black.xpm";
    image_path[2] = "sprites/Other/Pacdots/pacdot_food.xpm";
    image_path[3] = "pac_frames.xpm";
    image_path[4] = "sprites/Other/Portal/portal.xpm";
    image_path[5] = "sprites/Ghosts/R/red_ghost_frames.xpm";
    image_path[6] = "sprites/Ghosts/Y/red_yellow_frames.xpm";
    image_path[7] = "sprites/Ghosts/P/red_yellow_frames.xpm";
    image_path[8] = "sprites/Ghosts/O/red_yellow_frames.xpm";
    image_path[9] = "sprites/Ghosts/K/red_yellow_frames.xpm";
    image_path[10] = "sprites/Ghosts/G/red_yellow_frames.xpm";
    image_path[11] = "sprites/Ghosts/B/red_yellow_frames.xpm";
}

static void init_image_vars(t_game *game, t_vars **images)
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

void destroy_image(t_vars *img_var)
{
    t_game *game;

    game = get_game_instance();
    mlx_destroy_image(game->mlx, (void *)&img_var->image);
}

static int load_single_image(t_game *game, t_vars *img_var, char *path)
{
    img_var->image = mlx_xpm_file_to_image(game->mlx, path, 
        &img_var->width, &img_var->height);
    if (!img_var->image)
        return (-1);

    img_var->image_addr = mlx_get_data_addr(img_var->image, 
        &img_var->bpp, &img_var->line_size, &img_var->endian);
    if (!img_var->image_addr)
        return (-1);

    register_memory_allocation(get_memory_tracker(), 
        create_memory_record(img_var->image, destroy_image));
    return (0);
}

int load_images(t_game *game)
{
    char *image_path[12];
    t_vars *images[12];
    int i;

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

int render_game_map(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            if (game->map.map[i][j] == '0')
                render_map_tile(i,j,&game->floor,game);
             if (game->map.map[i][j] == '1')
                render_map_tile(i,j,&game->obstacl,game);
            else if (game->map.map[i][j] == 'C')
                render_map_tile(i,j,&game->collectable,game);
            else if (game->map.map[i][j] == 'E')
                render_map_tile(i,j,&game->portal,game);
            else if (game->map.map[i][j] == 'P')
                 initialize_character_position(i,j,&game->player,game);
            else if(game->map.map[i][j] == 'X')
                 initialize_character_position(i,j,&game->enemy[game->enemies_counter++],game);
            j++;
        }
        i++;
    }
    return (0);
}



static int init_mlx_and_window(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (-1);
        
    game->win = mlx_new_window(game->mlx, (game->map.width - 1) * SCALE,
        (game->map.height + 3) * SCALE, "so_long");
    if (!game->win)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        return (-1);
    }
    return (0);
}

static int init_canvas(t_game *game)
{
    game->canvas.image = mlx_new_image(game->mlx, game->map.width * SCALE,
        game->map.height * SCALE);
    if (!game->canvas.image)
    {
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        return (-1);
    }
    
    game->canvas.image_addr = mlx_get_data_addr(game->canvas.image, &game->canvas.bpp,
        &game->canvas.line_size, &game->canvas.endian);
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

static void setup_game_hooks(t_game *game)
{
    mlx_loop_hook(game->mlx, render_game_frame, game);
    mlx_hook(game->win, 2, 1L<<0, handle_player_movement_input, game);
}
int initialize_game_window(t_game *game)
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


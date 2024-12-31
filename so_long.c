#include "so_long.h"

int main(int ac, char **av)
{
    t_game game;

    if (ac != 2)
    {
        ft_putendl_fd("Error: wrong format <./so_long mapXX.ber>", 2);
        return (1);
    }

    ft_memset(&game, 0, sizeof(t_game));
    
    if (read_map(av[1], &game) == -1)
    {
        ft_putendl_fd("Error: Failed to read map", 2);
        return (1);
    }

    if (check_map_if_valid(&game) == -1)
    {
        ft_putendl_fd("Error: Map is NOT valid", 2);
        return (1);
    }

    if(initialize_game_window(&game) == -1)
    {
        ft_putendl_fd("Error: Failed to launch the game",2);
        free_map_resources(game.map.map, game.map.height);
        return (1);
    }

    for (int i = 0; i < game.map.height; i++)
        ft_putstr_fd(game.map.map[i], 1);

    return (0);
}
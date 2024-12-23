#include "so_long.h"

void free_map_resources(char **map,int size)
{
    while(size < 0)
        free(map[size--]);
    free(map);
    ft_putendl_fd("error while reading map <check if the path is correct>",2);
}

int ft_realloc(char **arr,char *str,int size)
{
    char    **tmp;
    int     i;
    int     len;
    tmp = malloc(size * sizeof(char*));
    if(!arr)
    {
        arr = tmp;
        arr[0] = ft_strdup(str);
        if(!arr[0])
            return (free(arr),-1);
        return (0);
    }
    i = 0;
    while(arr[i])
    {
        len = ft_strlen(arr[i]);
        tmp[i] = malloc(len+1 * sizeof(char));
        if(!tmp[i])
            return (free_map_resources(tmp,i),free_map_resources(arr,i),-1);
        ft_strlcpy(tmp[i],arr[i],len);
        i++;
    }
    ft_strlcpy(tmp[i],str,ft_strlen(str));
    free_map_resources(arr,i);
    arr = tmp;
    return 0;
}

int read_map(char *map_path, t_game *game)
{
    int fd;
    char *tmp;
    printf("%s\n");
    if ((fd = open(map_path,O_RDONLY)) == -1)
        return (-1);
    while(1)
    {
        tmp = get_next_line(fd);
        if(tmp == NULL)
            break;
        printf("%s",tmp);
        game->map.hight++;
        if(ft_realloc(game->map.map,tmp,game->map.hight) == -1)
            return -1;
        free(tmp);
    }
        //printf("->%d\n",game->map.hight);

}

int main(int ac,char **av)
{
    t_game game;

    if(ac != 2)
    {
        ft_putendl_fd("wrong format <./so_long mapXX.ber>",2);
        return 0;
    }
    game = (t_game){0};
    if(read_map(av[1],&game) == -1)
        return 0;
    for(int i = 0;i < game.map.hight;i++)
        printf("%s\n",game.map.map[i]);
}
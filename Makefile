CC = cc
CFLAGS = -Wall -Werror -Wextra
MSRCS = so_long.c map.c game_initializer.c game_utils.c\
 	game_animations.c game_movements.c rendering.c for_norm.c\
  	animation_core.c enemy_movement.c collision_handling.c\
  	enemy_ai.c game_state.c death_handler.c BFS_utiles.c BFS.c map_utils.c
	
LIBFT = libft.a
LIBFT_DIR = includes/libft
SO_LONG = so_long

all: $(LIBFT) $(SO_LONG)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(SO_LONG) : $(MSRCS)
	$(CC) $(CFLAGS) $(MSRCS) -o $(SO_LONG) -L$(LIBFT_DIR) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SO_LONG)

re: fclean all

.PHONY: all clean fclean re

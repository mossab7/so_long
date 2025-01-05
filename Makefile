CC = cc
CFLAGS = -Wall -Werror -Wextra
MSRCS = so_long.c map.c game_initializer.c game_utils.c\
 	game_animations.c game_movements.c rendering.c for_norm.c animation_core_utils.c\
  	animation_core.c enemy_movement.c collision_handling.c load_images_utils.c\
  	enemy_ai.c game_state.c death_handler.c BFS_utiles.c BFS.c map_utils.c

BSRCS = animation_core_bonus.c death_handler_bonus.c game_initializer_bonus.c load_images_utils_bonus.c\
	animation_core_utils_bonus.c enemy_ai_bonus.c game_movements_bonus.c\
	map_bonus.c so_long_bonus.c BFS_bonus.c enemy_movement_bonus.c game_state_bonus.c\
	BFS_utiles_bonus.c for_norm_bonus.c game_utils_bonus.c map_utils_bonus.c\
	collision_handling_bonus.c game_animations_bonus.c rendering_bonus.c

LIBFT = libft.a
LIBFT_DIR = includes/libft
SO_LONG = so_long
SO_LONG_BONUS = so_long_bonus

all: $(LIBFT) $(SO_LONG)


$(LIBFT):
	make -C $(LIBFT_DIR)

bonus :$(LIBFT) $(SO_LONG_BONUS)

$(SO_LONG) : $(MSRCS)
	$(CC) $(CFLAGS) $(MSRCS) -o $(SO_LONG) -L$(LIBFT_DIR) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

$(SO_LONG_BONUS) : $(BSRCS)
	$(CC) $(CFLAGS) $(BSRCS) -o $(SO_LONG) -L$(LIBFT_DIR) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SO_LONG)

re: fclean all

.PHONY: all clean fclean re

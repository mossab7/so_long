CC = cc
CFLAGS = -Wall -Werror -Wextra

MSRCS = mandatory/so_long.c mandatory/map.c mandatory/game_initializer.c mandatory/game_utils.c\
 	mandatory/game_animations.c mandatory/game_movements.c mandatory/rendering.c mandatory/for_norm.c mandatory/animation_core_utils.c\
  	mandatory/animation_core.c mandatory/enemy_movement.c mandatory/collision_handling.c mandatory/load_images_utils.c\
  	mandatory/enemy_ai.c mandatory/game_state.c mandatory/death_handler.c mandatory/BFS_utiles.c mandatory/BFS.c mandatory/map_utils.c

BSRCS = bonus/so_long.c bonus/map.c bonus/game_initializer.c bonus/game_utils.c\
 	bonus/game_animations.c bonus/game_movements.c bonus/rendering.c bonus/for_norm.c bonus/animation_core_utils.c\
  	bonus/animation_core.c bonus/enemy_movement.c bonus/collision_handling.c bonus/load_images_utils.c\
  	bonus/enemy_ai.c bonus/game_state.c bonus/death_handler.c bonus/BFS_utiles.c bonus/BFS.c bonus/map_utils.c

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
	$(CC) $(CFLAGS) $(BSRCS) -o $(SO_LONG_BONUS) -L$(LIBFT_DIR) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SO_LONG) $(SO_LONG_BONUS)

re: fclean all

.PHONY: all clean fclean re

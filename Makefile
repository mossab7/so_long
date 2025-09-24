CC = cc
CFLAGS = -Wall -Werror -Wextra

MSRCS = mandatory/so_long.c mandatory/map.c mandatory/game_initializer.c mandatory/game_utils.c\
 	mandatory/game_animations.c mandatory/game_movements.c mandatory/rendering.c mandatory/for_norm.c mandatory/animation_core_utils.c\
  	mandatory/animation_core.c mandatory/enemy_movement.c mandatory/collision_handling.c mandatory/load_images_utils.c mandatory/move_counter.c\
  	mandatory/enemy_ai.c mandatory/game_state.c mandatory/death_handler.c mandatory/BFS_utiles.c mandatory/BFS.c mandatory/map_utils.c

BSRCS = bonus/so_long_bonus.c bonus/map_bonus.c bonus/game_initializer_bonus.c\
 	bonus/game_utils_bonus.c bonus/game_animations_bonus.c bonus/game_movements_bonus.c\
  	bonus/rendering_bonus.c bonus/for_norm_bonus.c bonus/animation_core_utils_bonus.c\
   	bonus/animation_core_bonus.c bonus/enemy_movement_bonus.c bonus/collision_handling_bonus.c\
   	bonus/load_images_utils_bonus.c bonus/enemy_ai_bonus.c bonus/game_state_bonus.c bonus/move_counter_bonus.c\
    bonus/death_handler_bonus.c bonus/BFS_utiles_bonus.c bonus/BFS_bonus.c bonus/map_utils_bonus.c


LIBFT = libft.a
LIBFT_DIR = utils/libft
MLX_DIR = utils/minilibx-linux
SO_LONG = so_long
SO_LONG_BONUS = so_long_bonus

INCLUDES = -I$(LIBFT_DIR) -I$(MLX_DIR)

all: $(LIBFT) $(SO_LONG)

$(LIBFT):
	make -C $(LIBFT_DIR)

bonus :$(LIBFT) $(SO_LONG_BONUS)

$(SO_LONG) : $(MSRCS)
	$(CC) $(CFLAGS) $(MSRCS) -o $(SO_LONG) -L$(LIBFT_DIR) $(INCLUDES) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

$(SO_LONG_BONUS) : $(BSRCS)
	$(CC) $(CFLAGS) $(BSRCS) -o $(SO_LONG_BONUS) -L$(LIBFT_DIR) $(INCLUDES) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SO_LONG) $(SO_LONG_BONUS)

re: fclean all

.PHONY: all clean fclean re

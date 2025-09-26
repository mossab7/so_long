CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = src/so_long.c src/map.c src/game_initializer.c src/game_utils.c\
 	src/game_animations.c src/game_movements.c src/rendering.c src/for_norm.c src/animation_core_utils.c\
  	src/animation_core.c src/enemy_movement.c src/collision_handling.c src/load_images_utils.c src/move_counter.c\
  	src/enemy_ai.c src/game_state.c src/death_handler.c src/BFS_utiles.c src/BFS.c src/map_utils.c


LIBFT = libft.a
LIBFT_DIR = utils/libft
MLX_DIR = utils/minilibx-linux
SO_LONG = so_long

INCLUDES = -I$(LIBFT_DIR) -I$(MLX_DIR)

all: $(LIBFT) $(SO_LONG)

$(LIBFT):
	make -C $(LIBFT_DIR)


$(SO_LONG) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(SO_LONG) -L$(LIBFT_DIR) $(INCLUDES) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SO_LONG)

re: fclean all

.PHONY: all clean fclean re

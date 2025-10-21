CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = src/so_long.c src/map.c src/game_initializer.c src/game_utils.c \
	src/game_animations.c src/game_movements.c src/rendering.c src/for_norm.c \
	src/animation_core_utils.c src/animation_core.c src/enemy_movement.c \
	src/collision_handling.c src/load_images_utils.c \
	src/enemy_ai.c src/game_state.c src/death_handler.c src/BFS_utiles.c \
	src/BFS.c src/map_utils.c

HEADERS = src/so_long.h

OBJ_DIR = .obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

LIBFT = libft.a
LIBFT_DIR = utils/libft
MLX_DIR = utils/minilibx-linux
SO_LONG = so_long

INCLUDES = -Isrc -I$(LIBFT_DIR) -I$(MLX_DIR)

LDFLAGS = -L$(LIBFT_DIR) -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
MLX_INCLUDES = -Imlx_linux

all: $(LIBFT) $(SO_LONG)

run : $(SO_LONG)
	./$(SO_LONG)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(SO_LONG): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -o $(SO_LONG) $(LDFLAGS)

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(SO_LONG)
	make -C $(LIBFT_DIR) fclean

re: fclean all

show:
	@echo "SRC: $(SRC)"
	@echo "OBJ: $(OBJ)"
	@echo "HEADERS: $(HEADERS)"
	@echo "INCLUDES: $(INCLUDES)"

.PHONY: all clean fclean re show

CC = cc
CFLAGS = -Wall -Werror -Wextra
MSRCS = so_long.c
LIBFT = libft.a
LIBFT_DIR = includes/libft
SO_LONG = so_long

all: $(LIBFT) $(SO_LONG)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(SO_LONG) : $(MSRCS)
	$(CC)  $(MSRCS) -o $(SO_LONG) -L$(LIBFT_DIR) -lft

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SO_LONG)

re: fclean all

.PHONY: all clean fclean re

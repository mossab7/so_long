CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRCS = ft_atoi.c  ft_split.c ft_strdup.c  ft_putendl_fd.c ft_substr.c ft_strmapi.c\
       ft_strtrim.c ft_calloc.c  ft_putstr_fd.c ft_strnstr.c ft_isalnum.c \
       ft_bzero.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c  \
       ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c  get_next_line.c\
       ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c  ft_strncmp.c \
       ft_tolower.c ft_toupper.c ft_strchr.c ft_strjoin.c \
       ft_strrchr.c ft_itoa.c ft_putnbr_fd.c ft_putchar_fd.c ft_striteri.c \
        ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
        ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_abs.c \
        ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c resource_manager.c resource_manager_utiles.c

OBJS = $(SRCS:.c=.o)

HEADER = libft.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS) 

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <mbouhia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:08:49 by mbouhia           #+#    #+#             */
/*   Updated: 2024/10/25 21:06:23 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void					*content;
	struct s_list			*next;
}							t_list;

typedef struct stored_s
{
	char					*content;
	size_t					last_pos;
}							t_stored;

typedef struct s_alloc_record
{
	void					*ptr;
	void					(*free_func)(void *);
	struct s_alloc_record	*next;
}							t_alloc_record;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

int							ft_atoi(const char *str);
void						ft_putendl_fd(char const *s, int fd);
void						ft_striteri(char *s, void (*f)(unsigned int,
									char *));
t_list						*ft_lstmap(t_list *lst, void *(*f)(void *),
								void (*del)(void *));
void						ft_lstiter(t_list *lst, void (*f)(void *));
t_list						*ft_lstlast(t_list *lst);
void						ft_lstclear(t_list **lst, void (*del)(void *));
void						ft_lstdelone(t_list *lst, void (*del)(void *));
t_list						*ft_lstnew(void *content);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);
void						ft_lstadd_back(t_list **lst, t_list *new);
void						ft_lstadd_front(t_list **lst, t_list *new);
int							ft_lstsize(t_list *lst);
char						*ft_strmapi(char const *s, char (*f)(unsigned int,
									char));
void						ft_putnbr_fd(int n, int fd);
char						*ft_itoa(int n);
void						ft_putstr_fd(char const *s, int fd);
char						*ft_strjoin(char const *s1, char const *s2);
void						ft_putchar_fd(char c, int fd);
char						**ft_split(char *str, char c);
char						*ft_strtrim(char const *s, char const *set);
void						*ft_calloc(size_t nmemb, size_t size);
void						ft_bzero(void *s, size_t n);
int							ft_isalpha(int c);
int							ft_isalnum(int c);
int							ft_isascii(int c);
int							ft_isdigit(int c);
int							ft_isprint(int c);
void						*ft_memchr(const void *s, int c, size_t n);
int							ft_memcmp(const void *s1, const void *s2, size_t n);
void						*ft_memcpy(void *dest, const void *src, size_t n);
void						*ft_memmove(void *dest, const void *src, size_t n);
void						*ft_memset(void *s, int c, size_t n);
char						*ft_strdup(const char *src);
size_t						ft_strlcat(char *dest, const char *src,
								size_t size);
size_t						ft_strlcpy(char *dest, const char *src,
								size_t size);
size_t						ft_strlen(const char *str);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
char						*ft_strnstr(const char *str, const char *to_find,
								size_t size);
int							ft_tolower(int c);
int							ft_toupper(int c);
char						*ft_strchr(const char *str, int c);
char						*ft_strrchr(const char *str, int c);
char						*extract_line(t_stored *stored);
char						*ft_linechr(t_stored *stored, int c);
char						*free_stored(char **content);
size_t						read_to_buffer(t_stored *stored, int fd);
void						ft_strmerge(char **dest, char *src);
char						*get_next_line(int fd);
t_alloc_record				**get_memory_tracker(void);
t_alloc_record				*create_memory_record(void *ptr,
								void (*deallocator)(void *));
void						register_memory_allocation(
								t_alloc_record **memory_records,
								t_alloc_record *new_record);
void						handle_allocation_failure(void *ptr);
void						*allocate_tracked_memory(size_t size);
void						cleanup_memory_tracker(
								t_alloc_record **memory_records);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:40:42 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/09 22:40:44 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

typedef struct stored_s
{
	char	*content[OPEN_MAX];
	size_t	last_pos;
}			t_stored;

char		*get_next_line(int fd);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_strmerge(char **dest, char *src);
size_t		ft_strlen(const char *s);
char		*free_stored(char **content);
size_t		read_to_buffer(t_stored *stored, int fd);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strdup(const char *s1);
char		*extract_line(t_stored *stored, int fd);
char		*ft_strchr(t_stored *stored, int c, int fd);

#endif

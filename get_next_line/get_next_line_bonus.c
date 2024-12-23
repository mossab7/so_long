/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:40:03 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/10 11:32:48 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(t_stored *stored, int c, int fd)
{
	size_t	i;

	i = stored->last_pos;
	if (!stored->content[fd])
		return (NULL);
	while (stored->content[fd][i])
	{
		if (stored->content[fd][i] == (char)c)
		{
			stored->last_pos = i;
			return (&stored->content[fd][i]);
		}
		i++;
	}
	stored->last_pos = i;
	if ((char)c == '\0')
		return (&stored->content[fd][i]);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*extract_line(t_stored *stored, int fd)
{
	char	*line;
	char	*remaining;

	if (stored->content[fd][stored->last_pos] == '\n')
		stored->last_pos++;
	line = ft_substr(stored->content[fd], 0, stored->last_pos);
	if (!line)
	{
		return (free_stored(&(stored->content[fd])));
	}
	if (stored->content[fd][stored->last_pos])
	{
		remaining = ft_strdup(&stored->content[fd][stored->last_pos]);
		if (!remaining)
		{
			free(line);
			return (free_stored(&(stored->content[fd])));
		}
	}
	else
		remaining = NULL;
	free(stored->content[fd]);
	stored->content[fd] = remaining;
	return (line);
}

size_t	read_to_buffer(t_stored *stored, int fd)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (bytes_read);
	}
	buffer[bytes_read] = '\0';
	temp = ft_strjoin(stored->content[fd], buffer);
	free(buffer);
	if (!temp)
		return (-1);
	free(stored->content[fd]);
	stored->content[fd] = temp;
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static t_stored	stored;
	ssize_t			bytes_read;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stored.last_pos = 0;
	while ((!stored.content[fd]) || !ft_strchr(&stored, '\n', fd))
	{
		bytes_read = read_to_buffer(&stored, fd);
		if (bytes_read < 0)
		{
			free (stored.content[fd]);
			stored.content[fd] = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
	}
	if (!stored.content[fd])
		return (NULL);
	return (extract_line(&stored, fd));
}

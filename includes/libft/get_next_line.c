/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:39:55 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/10 11:32:22 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_stored(char **content)
{
	free(*content);
	*content = NULL;
	return (NULL);
}

char	*ft_linechr(t_stored *stored, int c)
{
	size_t	i;

	i = stored->last_pos;
	if (!stored->content)
		return (NULL);
	while (stored->content[i])
	{
		if (stored->content[i] == (char)c)
		{
			stored->last_pos = i;
			return (&stored->content[i]);
		}
		i++;
	}
	stored->last_pos = i;
	if ((char)c == '\0')
		return (&stored->content[i]);
	return (NULL);
}

char	*extract_line(t_stored *stored)
{
	char	*line;
	char	*remaining;

	if (stored->content[stored->last_pos] == '\n')
		stored->last_pos++;
	line = ft_substr(stored->content, 0, stored->last_pos);
	if (!line)
	{
		return (free_stored(&(stored->content)));
	}
	if (stored->content[stored->last_pos])
	{
		remaining = ft_strdup(&stored->content[stored->last_pos]);
		if (!remaining)
		{
			free(line);
			return (free_stored(&(stored->content)));
		}
	}
	else
		remaining = NULL;
	free(stored->content);
	stored->content = remaining;
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
	temp = ft_strjoin(stored->content, buffer);
	free(buffer);
	if (!temp)
		return (-1);
	free(stored->content);
	stored->content = temp;
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static t_stored	stored;
	ssize_t			bytes_read;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stored.last_pos = 0;
	while (!stored.content || !ft_linechr(&stored, '\n'))
	{
		bytes_read = read_to_buffer(&stored, fd);
		if (bytes_read < 0)
		{
			free (stored.content);
			stored.content = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
	}
	if (!stored.content)
		return (NULL);
	return (extract_line(&stored));
}
